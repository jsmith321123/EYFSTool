#include "NewAssessmentScreen.h"
#include <QStringList>

#include <QSqlQuery>
#include <QSqlDatabase>

#include <fstream>

#include <time.h>

#include "./../../libraries/json.hpp"

using namespace std;
using json = nlohmann::json;

NewAssessmentScreen::NewAssessmentScreen () {
    createSelectLayout();

    setLayout(&layout);

    getAreas();

    createAssessmentLayout();

    //set the first area to be 0
    setArea(0);

    //connections
    connect(&submitButton, SIGNAL(clicked()), this, SLOT(selectChild()));
    connect(&areaSet, SIGNAL(clicked()), this, SLOT(setAreaSlot()));
    connect(&subareaSet, SIGNAL(clicked()), this, SLOT(setSubareaSlot()));
    connect(&nextButton, SIGNAL(clicked()), this, SLOT(nextAgeRange()));
    connect(&backButton, SIGNAL(clicked()), this, SLOT(lastAgeRange()));
    connect(&selectButton, SIGNAL(clicked()), this, SLOT(selectAgeRange()));
    connect(&subareaNext, SIGNAL(clicked()), this, SLOT(nextSubarea()));
    connect(&subareaBack, SIGNAL(clicked()), this, SLOT(lastSubarea()));
    connect(&saveButton, SIGNAL(clicked()), this, SLOT(saveAssessment()));
    connect(&areaNext, SIGNAL(clicked()), this, SLOT(nextArea()));
    connect(&areaBack, SIGNAL(clicked()), this, SLOT(lastArea()));
}

void NewAssessmentScreen::selectChild() {
    layout.setCurrentIndex(1);

    name = childSelection.currentText().toStdString();
    term = termSelection.currentText().toStdString();
    year = getYear(term);

    id = childSelection.currentIndex();

    cout << name << endl;
    cout << term << endl;
    cout << year << endl;

    loadAssessment();
}

string NewAssessmentScreen::getYear(string term) {
    time_t theTime = time(NULL);
    struct tm *aTime = localtime(&theTime);

    int month = aTime->tm_mon + 1;
    int year = aTime->tm_year + 1900;

    if (term == "Autumn" && month < 7) {
        year--;
    }

    return to_string(year);
}

void NewAssessmentScreen::createSelectLayout() {
    //update the list of child names
    updateList();

    //add the child selection box to the layout
    selectionLayout.addWidget(&childSelection);

    //create a new list with the terms for
    //the term oombo box then add the box
    //to the layout
    QStringList terms;
    terms << "Autumn" << "Spring" << "Summer";

    termSelection.insertItems(0, terms);

    selectionLayout.addWidget(&termSelection);

    //set the text of the submit button then
    //add it to the layout
    submitButton.setText("Submit");

    selectionLayout.addWidget(&submitButton);

    //make widgets align toward the top with no gaps
    selectionLayout.setAlignment(Qt::AlignTop);

    //add the layout to the selection widget
    //then add that widget to the stacked
    //layout for the page
    selectionWidget.setLayout(&selectionLayout);
    layout.addWidget(&selectionWidget);
}

void NewAssessmentScreen::updateList() {
    QStringList items;

    ifstream child_file("./data/children.json", ifstream::binary);
    json child_json(child_file);

    for (json child : child_json) {
            string surname = child["surname"].dump();
            surname = surname.substr(1, surname.length() -2);

            string forename = child["forename"].dump();
            forename = forename.substr(1, forename.length() -2);

            items << QString::fromStdString(surname + ", " + forename);
        }

        childSelection.insertItems(0, items);
}

void NewAssessmentScreen::createAssessmentLayout() {
    //add all of the widgets to the
    //assessment layout

    areaBack.setText("Back");
    areaSet.setText("Select Area");
    areaNext.setText("Next");

    subareaBack.setText("Back");
    subareaSet.setText("Select Sub-Area");
    subareaNext.setText("Next");

    areaLayout.addWidget(&areaBack);
    areaLayout.addWidget(&areaCb);
    areaLayout.addWidget(&areaSet);
    areaLayout.addWidget(&areaNext);
    assessLayout.addLayout(&areaLayout);

    subareaLayout.addWidget(&subareaBack);
    subareaLayout.addWidget(&subareaCb);
    subareaLayout.addWidget(&subareaSet);
    subareaLayout.addWidget(&subareaNext);
    assessLayout.addLayout(&subareaLayout);

    assessLayout.addWidget(&text);

    //set text of the buttons
    backButton.setText("Back");
    selectButton.setText("Select");
    saveButton.setText("Save");
    nextButton.setText("Next");

    buttonLayout.addWidget(&backButton);
    buttonLayout.addWidget(&selectButton);
    buttonLayout.addWidget(&saveButton);
    buttonLayout.addWidget(&nextButton);

    assessLayout.addLayout(&buttonLayout);
    assessWidget.setLayout(&assessLayout);

    layout.addWidget(&assessWidget);
}

void NewAssessmentScreen::getAreas() {
    QStringList areas;

    ifstream details_file("./data/assessment_details.json", ifstream::binary);
    json details_json(details_file);

    details_json_ = details_json;

    for (json area : details_json) {
        string title = area["area"].dump();
        areas << QString::fromStdString(title.substr(1, title.length() - 2));

        QStringList subas;
        for (json subarea : area["subareas"]) {
            string titlesa = subarea["title"].dump();
            subas << QString::fromStdString(titlesa.substr(1, titlesa.length() - 2));
        }

        subareas.push_back(make_pair(QString::fromStdString(title), subas));
    }

    areaCb.insertItems(0, areas);
    subareaCb.insertItems(0, subareas[areaIndex].second);
}

void NewAssessmentScreen::setArea(int index) {
    //set the subarea index to 0 if the area
    //index has changed and also update the
    //list of subareas
    if (areaIndex != index) {
        subareaIndex = 0;

        //set the new subareas in the subarea box
        subareaCb.clear();
        subareaCb.insertItems(0, subareas[index].second);
    }
    
    areaIndex = index;

    string range_text;

    for (json point : details_json_[areaIndex]["subareas"][subareaIndex]["age-ranges"][ageRange]["text"]) {
        range_text += "- " + point.dump().substr(1, point.dump().length() - 2) + "\n";
    }

    text.setText(
            "Age range: " + ranges[ageRange] + "\n"
            + QString::fromStdString(range_text)
        );
}

void NewAssessmentScreen::setSubarea(int index) {
    subareaIndex = index;

    setArea(areaIndex);
}

void NewAssessmentScreen::setAgeRange(int index) {
    ageRange = index;

    setArea(areaIndex);
}

void NewAssessmentScreen::setAreaSlot() {
    setArea(areaCb.currentIndex());
}

void NewAssessmentScreen::setSubareaSlot() {
    setSubarea(subareaCb.currentIndex());
}

void NewAssessmentScreen::nextAgeRange() {
    //skip to the last area and sub area
    //if needed
    if (ageRange < ranges.size() - 1) {
        setAgeRange(ageRange + 1);
    }
}

void NewAssessmentScreen::lastAgeRange() {
    //skip to the last area and sub area
    //if needed
    if (ageRange > 0) {
        setAgeRange(ageRange - 1);
    }
}

void NewAssessmentScreen::nextSubarea() {
    if (subareaIndex + 1 < subareas[areaIndex].second.size()) {
            setSubarea(subareaIndex + 1);

            subareaCb.setCurrentIndex(subareaIndex);

            setAgeRange(0);
    } else if (areaIndex + 1 < subareas.size()) {
            setArea(areaIndex + 1);

            areaCb.setCurrentIndex(areaIndex);

            setAgeRange(0);
    } else {
        saveAssessment();
    }
}

void NewAssessmentScreen::lastSubarea() {
    if (subareaIndex - 1 >= 0)  {
            setSubarea(subareaIndex - 1);

            subareaCb.setCurrentIndex(subareaIndex);

            setAgeRange(ranges.size() -1);
        } else {
            if (areaIndex - 1 >= 0) {
                setArea(areaIndex - 1);
                setSubarea(subareas[subareaIndex].second.size() - 1);

                areaCb.setCurrentIndex(areaIndex);
                subareaCb.setCurrentIndex(subareas[subareaIndex].second.size() - 1);

                setAgeRange(ranges.size() -1);
            }
        }
}

void NewAssessmentScreen::nextArea() {
    if (areaIndex + 1 < subareas.size()) {
        setArea(areaIndex + 1);

        areaCb.setCurrentIndex(areaIndex);

        setAgeRange(0);
    } else {
        saveAssessment();
    }
}

void NewAssessmentScreen::lastArea() {
    if (areaIndex - 1 >= 0) {
        setArea(areaIndex - 1);
        setSubarea(subareas[subareaIndex].second.size() - 1);

        areaCb.setCurrentIndex(areaIndex);
        subareaCb.setCurrentIndex(subareas[subareaIndex].second.size() - 1);

        setAgeRange(ranges.size() -1);
    }
}

void NewAssessmentScreen::selectAgeRange() {
    //create a new json object for this
    //area and then add it to to the results


    json curr_area = json();
    string current_suba = subareas[areaIndex].second[subareaIndex].toStdString();

    //find if the subarea selected exists
    bool found = false;
    int foundIndex;
    int i = 0;

    for (string sa : completedSa) {
        if (sa == current_suba) {
            found = true;
            foundIndex = i;
        }

        i += 1;
    }

    //add the data to the empty json
    curr_area["title"] = current_suba;
    curr_area["age_range"] = ageRange;

    //add a new json object to the results list
    //only if the current subarea hasnt been selected
    //if it has then replace the old data with the
    //new data
    if (!found) {
        results_json_.push_back(curr_area);

        completedSa.push_back(current_suba);
    } else {
        results_json_[foundIndex] = curr_area;
    }

    //move to the next subarea
    nextSubarea();
}

void NewAssessmentScreen::saveAssessment() {
    //if there are no assessments
    //for the current child
    //initialise a new json with
    // the correct format
    bool childExists = true;

    if (child_ == json()) {
        child_["id"] = id;
        child_["type"] = "individual";

        childExists = false;
    }

    //add the newly carried out
    //assessment to the child's
    //object
    bool assessExists = false;
    int foundIndex;
    int i = 0;

    //see if there already exists an
    //assessment for this term and year
    for (json assess : child_["assessments"]) {
        if (assess["term"] == json(term) && assess["year"] == json(year)) {
            assessExists = true;
            foundIndex = i;
        }

        i++;
    }

    //if the assessment exists,
    //modify the existing record,
    //if not add a new one
    if (!assessExists) {
        child_["assessments"][child_["assessments"].size()]["areas"] = results_json_;
        child_["assessments"][child_["assessments"].size() - 1]["term"] = term;
        child_["assessments"][child_["assessments"].size() - 1]["year"] = year;
    } else {
        child_["assessments"][foundIndex]["areas"] = results_json_;
        child_["assessments"][foundIndex]["term"] = term;
        child_["assessments"][foundIndex]["year"] = year;
    }

    //if the child exists modify
    //the existing object, if not
    //add a new one to the end of the file
    if (childExists) {
        oldAssJson[childIndex] = child_;
    } else {
        oldAssJson.push_back(child_);
    }

    ofstream output("./data/assessments.json");
    output << oldAssJson.dump();

    //go back to the child selection screen
    //and reset the areas
    layout.setCurrentIndex(0);

    areaIndex = 0;
    subareaIndex = 0;
    ageRange = 0;
}

void NewAssessmentScreen::loadAssessment() {
    ifstream oldAssFile("./data/assessments.json", ifstream::binary);
    oldAssJson = json::parse(oldAssFile);

    int i = 0;

    for (json child : oldAssJson) {
        if (child["id"] == json(id)) {
            child_ = child;

            childIndex = i;
        }

        i++;
    }  
}
