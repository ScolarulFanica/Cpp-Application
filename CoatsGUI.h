#pragma once
#include <qwidget.h>
#include "TrenchCoat.h"
#include "Service.h"
#include "Repository.h"
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QShortcut>

class CoatsGUI : public QWidget
{
	Q_OBJECT

public:
	CoatsGUI(std::vector<Coat> coats, QWidget* parent = nullptr);
	~CoatsGUI();

private:
	Repository* repo;
	Service* serv;
	std::vector<Coat> coats;
	QListWidget* coatsList;
	QSpinBox* sizeSpinBox;
	QLineEdit* colourEdit;
	QDoubleSpinBox* priceSpinBox;
	QSpinBox* quantitySpinBox;
	QTextEdit* photographEdit;
	QPushButton* addCoatButton;
	QPushButton* deleteCoatButton;
	QPushButton* updateCoatButton;
	QShortcut* undoShortcut;
	QShortcut* redoShortcut;

	/*
	Add multiple undo and redo functionality for the add, remove, and update operations.
	Implement this functionality using inheritance and polymorphism.
	You will have Undo and Redo buttons on the GUI, as well as a key combination to undo and redo the operations (e.g. Ctrl+Z, Ctrl+Y).
	*/

	QPushButton* undoButton;
	QPushButton* redoButton;

	void initGUI();
	int getSelectedIndex();
	void connectSignalsAndSlots();

	void populateCoatsList();
	// When an item in the list is clicked, the text boxes get filled with the item's information
	void listItemChanged();

	void addCoatButtonHandler();
	void deleteCoatButtonHandler();
	void updateCoatButtonHandler();
	void undoButtonHandler();
	void redoButtonHandler();

signals:
	void coatsUpdatedSignal();
	void addCoatSignal(const int& size, const string& colour, const double& price, const int& quantity, const string& photograph);
	void updateCoatSignal(const int& size, const string& colour, const double& price, const int& quantity, const string& photograph);

public slots:
	void addCoat(const int& size, const string& colour, const double& price, const int& quantity, const string& photograph);
	void updateCoat(const int& size, const string& colour, const double& price, const int& quantity, const string& photograph);
};

