#include "OOPA89.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QLineEdit>
#include <QPushButton>

#include <iostream>
#include "UI.h"
#include "GUI.h"
#include "ADMINGUI.h"
#include "USERGUI.h"
#include "Services.h"
#include "Repository.h"
#include "RepositoryWL.h"
#include "Movie.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Repository* repository = new Repository();
    RepositoryWL* repositoryWL = new RepositoryWL();
    Services* services = new Services(repository, repositoryWL);
    GUI gui = GUI(services);
    //UI ui = UI(services);

    gui.show();
    //ui.run();

    return a.exec();

}

