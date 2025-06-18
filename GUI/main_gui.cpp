#include "LoginWindow.h"
#include <QApplication>
#include "DatabaseManager.h"

int main(int argc, char* argv[])
{    
    QApplication app(argc, argv);
    if (!DatabaseManager::instance().connect()) {
        qWarning() << "Failed to connect to database!";
        return -1;
    }

    LoginWindow window;
    window.show();
    return app.exec();
}
