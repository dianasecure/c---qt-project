#pragma once
#include <qwidget.h>
#include <qmainwindow.h>
#include "Services.h"
#include "AdminGUI.h"
#include "UserGUI.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <QHBoxLayout>


class GUI : public QWidget {
private:

	Services* services;
	ADMINGUI adminGUI = ADMINGUI(services);
	USERGUI userGUI = USERGUI(services);

	QPushButton* adminButton;
	QPushButton* userButton;

public:
	GUI(Services* services);
	~GUI();

private:
	void mainGUI();
	void adminMode();
	void userMode();

};
