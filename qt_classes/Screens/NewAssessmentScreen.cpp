#include "NewAssessmentScreen.h"
#include <QStringList>

#include <fstream>

#include <time.h>

#include "./../../libraries/json.hpp"

#include "NewGroupDialog.h"

using namespace std;
using json = nlohmann::json;

NewAssessmentScreen::NewAssessmentScreen () {
    createSelectLayout();

    setLayout(&layout);

    getAreas();

    createAssessmentLayout();

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

    //set the first area to be 0
    setArea(0);
    setSubarea(0);
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
    //set the subarea index to 0 or the last
    //assessed age range if the area
    //index has changed and also update the
    //list of subareas
    if (areaIndex != index) {
        setSubarea(0);

        //set the new subareas in the subarea box
        subareaCb.clear();
        subareaCb.insertItems(0, subareas[index].second);
    }
    
    areaIndex = index;

    string range_text;

    for (json point : details_json_[areaIndex]["subareas"][subareaIndex]["age-ranges"][ageRange]["text"]) {
        range_text += "- " + point.dump().substr(1, point.dump().length() - 2) + "\n";
    }

    bool subareaCompleted = false;

    for (string sa : completedSa) {
        if (sa == subareas[areaIndex].second[subareaIndex].toStdString()) {
            subareaCompleted = true;
        }
    }

    QString sSubAreaComplete = (subareaCompleted) ?
                               (QString("yes")) : (QString("no"));

    text.setText(
            "Age range: " + ranges[ageRange] + "\n"
            + "Sub-Area complete: " + sSubAreaComplete + "\n"
            + QString::fromStdString(range_text)
        );
}

void NewAssessmentScreen::setSubarea(int index) {
    subareaIndex = index;
    subareaCb.setCurrentIndex(index);

    if (prev_assessment_json != json()) {
        cout << prev_assessment_json << endl;
        if (prev_assessment_json["areas"][getIndex(areaIndex, subareaIndex)] != NULL) {
            int ar = prev_assessment_json["areas"][getIndex(areaIndex, subareaIndex)]["age_range"];
            setAgeRange(ar);
        } else {
            setAgeRange(0);
        }
    } else {
        setAgeRange(0);
    }

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
    } else if (areaIndex + 1 < subareas.size()) {
            setArea(areaIndex + 1);

            areaCb.setCurrentIndex(areaIndex);
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

    //add the data to the empty json
    curr_area["title"] = current_suba;
    curr_area["age_range"] = ageRange;

    //update the results with the new
    //age range
    results_json_[getIndex(areaIndex, subareaIndex)] = curr_area;

    //move to the next subarea
    nextSubarea();
}

int NewAssessmentScreen::getIndex(int a, int s) {
    int index = 0;
    bool found = false;

    QString target = subareas[a].second[s];

    for (pair<QString, QStringList> ar : subareas) {
        for (QString su : ar.second) {
            index++;
            if (su == target) {
                found = true;
                break;
            }
        }

        if (found) {
            break;
        }
    }

    return index -1;
}

void NewAssessmentScreen::saveAssessment() {
    //if at least one area has been
    //selected update the json
    if (results_json_ != NULL) {
        //set the areas field of the json
        //to the results
        assessment_json["areas"] = results_json_;

        //add this assessment to the childs
        //object
        child_["assessments"][assessIndex] = assessment_json;

        //add this child to the whole json
        oldAssJson[childIndex] = child_;
    }

    //save the json
    ofstream output("./data/assessments.json");
    output << oldAssJson.dump();

    layout.setCurrentIndex(0);
    results_json_ = json();

    setArea(0);
    setSubarea(0);
    setAgeRange(0);
}

void NewAssessmentScreen::loadAssessment() {
    //open the file and parse the json
    ifstream oldAssFile("./data/assessments.json", ifstream::binary);
    oldAssJson = json::parse(oldAssFile);
    oldAssFile.close();

    //find the child and its index
    bool childFound = false;
    int x = 0;

    for (json child : oldAssJson) {
        if (child["id"].dump() == to_string(id)) {
            child_ = child;
            childFound = true;
            childIndex = x;
        }

        x++;
    }

    //if the child wasn't found
    //create a json with the
    //correct format
    if (!childFound) {
        child_ = json();

        child_["id"] = id;
        child_["type"] = "individual";

        assessment_json = json();
        assessment_json["term"] = term;
        assessment_json["year"] = year;
        assessIndex = 0;

        childIndex = x;
    } else {
        //if the child is found
        //see if this assessment
        //allready exists
        bool assessFound = false;
        int i = 0;

        for (json assess : child_["assessments"]) {
            //if it exists get the index and
            //add all its completed subareas
            //to the completedSA vector
            if (assess["year"] == json(year) && assess["term"] == json(term)) {
                assessment_json = assess;
                results_json_ = assess["areas"];
                assessFound = true;
                assessIndex = i;

                //add all of the completed subareas
                //to the vector
                for (json area : results_json_) {
                    string title = area["title"];
                    completedSa.push_back(title);
                }
            }

            i++;
        }

        //if there was no previous
        //assessment create one with the
        //correct format
        if (!assessFound) {
            assessment_json = json();
            assessment_json["term"] = term;
            assessment_json["year"] = year;
            assessIndex = i;
        }

        //if there is a previous assessment
        //find it
        if (assessIndex > 0) {
            prev_assessment_json = child_["assessments"][assessIndex - 1];
        }
    }
}
