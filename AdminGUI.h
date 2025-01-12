#pragma once
#include <qwidget.h>
#include "Services.h"
#include <qlistwidget.h>
#include <qlineedit.h>
#include <qpushbutton.h>

class ADMINGUI : public QWidget
{
private:
	Services* services;

	QListWidget* moviesWidget;
	QLineEdit* titleEdit;
	QLineEdit* genreEdit;
	QLineEdit* yearEdit;
	QLineEdit* likesEdit;
	QLineEdit* linkEdit;

	QPushButton* addButton;
	QPushButton* deleteButton;
	QPushButton* updateButton;

public:
	ADMINGUI(Services* services);
	~ADMINGUI();

private:
	void buildADMINGUI();
	void populateList();

	void addButtonHandler();
	void deleteButtonHandler();
	void updateButtonHandler();

};