#include "NewAssessmentScreen.h"
#include <QStringList>

#include <QSqlQuery>
#include <QSqlDatabase>

#include <fstream>

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
}

void NewAssessmentScreen::selectChild() {
    layout.setCurrentIndex(1);

    name = childSelection.currentText().toStdString();
    term = termSelection.currentText().toStdString();
    year = "2016";

    id = childSelection.currentIndex();

    cout << name << endl;
    cout << term << endl;
    cout << year << endl;
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

    areaSet.setText("Select Area");
    subareaSet.setText("Select Sub-Area");

    areaLayout.addWidget(&areaCb);
    areaLayout.addWidget(&areaSet);
    assessLayout.addLayout(&areaLayout);

    subareaLayout.addWidget(&subareaCb);
    subareaLayout.addWidget(&subareaSet);
    assessLayout.addLayout(&subareaLayout);

    assessLayout.addWidget(&text);

    //set text of the buttons
    backButton.setText("Back");
    selectButton.setText("Select");
    nextButton.setText("Next");

    buttonLayout.addWidget(&backButton);
    buttonLayout.addWidget(&selectButton);
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
    if (ageRange == ranges.size() -1) {
        nextSubarea();
    } else {
        setAgeRange(ageRange + 1);
    }
}

void NewAssessmentScreen::lastAgeRange() {
    //skip to the last area and sub area
    //if needed
    if (ageRange == 0) {
        lastSubarea();
    } else {
        setAgeRange(ageRange - 1);
    }
}

void NewAssessmentScreen::nextSubarea() {
    if (subareaIndex + 1 < subareas[areaIndex].second.size()) {
            setSubarea(subareaIndex + 1);

            subareaCb.setCurrentIndex(subareaIndex);

            setAgeRange(0);
        } else {
            if (areaIndex + 1 < subareas.size()) {
                setArea(areaIndex + 1);

                areaCb.setCurrentIndex(areaIndex);

                setAgeRange(0);
            }
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

void NewAssessmentScreen::selectAgeRange() {
    //create a new json object for this
    //area and then add it to to the results


    json curr_area = json();
    string current_suba = subareas[areaIndex].second[subareaIndex].toStdString();

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

    curr_area["title"] = current_suba;
    curr_area["age_range"] = ageRange;

    if (!found) {
        results_json_.push_back(curr_area);

        completedSa.push_back(current_suba);
    } else {
        results_json_[foundIndex] = curr_area;
    }

    nextSubarea();

    cout << results_json_ << endl;
}
