#include "GUI.h"
#include <qlayout.h>
#include <qlabel.h>

GUI::GUI(Services* services) : services{ services } {
	this->mainGUI();

	QWidget::connect(this->adminButton, &QPushButton::clicked, this, &GUI::adminMode);
	QWidget::connect(this->userButton, &QPushButton::clicked, this, &GUI::userMode);
}

GUI::~GUI() {

}

void GUI::mainGUI() {

	QHBoxLayout* mainLayout = new QHBoxLayout{ this };

	QGridLayout* buttons = new QGridLayout{};
	this->adminButton = new QPushButton{ "Admin" };
	this->userButton = new QPushButton{ "User" };

	buttons->addWidget(adminButton);
	buttons->addWidget(userButton);

	mainLayout->addLayout(buttons);

	QWidget* mainWindow = new QWidget{ this };
	mainWindow->resize(500, 250);
	mainWindow->setLayout(mainLayout);

}

void GUI::adminMode() {

	this->adminGUI.show();

}

void GUI::userMode() {

	this->userGUI.show();
}
