#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMainWindow>
#include "UserGUI.h" 
#include "CoatsGUI.h" 
#include "CoatChartWidget.h"

/*
Show the contents of the adoption list / movie watch list / shopping basket / tutorial watch list using a table view.
You must use the Qt View/Model components (QTableView). Create your own model – a class which inherits from QAbstractTableModel.
This window will be opened from your GUI's main window.
*/

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr) : QMainWindow(parent) {
        // Create buttons
        QPushButton* adminButton = new QPushButton("Admin Mode", this);
        QPushButton* userButton = new QPushButton("User Mode", this);
        QPushButton* chartButton = new QPushButton("Show Chart", this);

        // Create layout
        QVBoxLayout* layout = new QVBoxLayout();
        layout->addWidget(adminButton);
        layout->addWidget(userButton);
        layout->addWidget(chartButton);

        // Create a central widget and set the layout
        QWidget* centralWidget = new QWidget(this);
        centralWidget->setLayout(layout);
        setCentralWidget(centralWidget);

        // Connect buttons to slots
        connect(adminButton, &QPushButton::clicked, this, &MainWindow::enterAdminMode);
        connect(userButton, &QPushButton::clicked, this, &MainWindow::enterUserMode);
        connect(chartButton, &QPushButton::clicked, this, &MainWindow::showChart);
    }

private slots:
    void enterAdminMode() {
        std::vector<Coat> coats{ Coat{ 46,"black",129.99,10,"Petrescu Rares" }, Coat{ 29,"bleumarin",89.99,2,"Ionescu Ion" }, Coat{ 52,"black",229.99,15,"Popescu Maria" } }; Repository repo; Service serv{ repo };
        CoatsGUI* adminGUI = new CoatsGUI(coats);
        adminGUI->show();
    }

    void enterUserMode() {
    UserGUI* userGUI = new UserGUI();
    userGUI->show();

    // Create a ShoppingBasketGUI model
    ShoppingBasketGUI* model = new ShoppingBasketGUI(userGUI->getShoppingBasket()->getRepo());

    // Update the model with data from the shopping basket
    model->updateData(userGUI->getShoppingBasket()->getAll());

    QTableView* view = new QTableView;
    view->setModel(model);
    view->show();
    }

    void showChart() {
        std::vector<Coat> coats; Repository repo; Service serv{ repo };
        CoatChartWidget* chartWidget = new CoatChartWidget(coats);
        chartWidget->show();
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}

#include "main.moc" // Include the moc file if not using CMake
