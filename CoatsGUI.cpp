#include "CoatsGUI.h"
#include <QDebug>

CoatsGUI::CoatsGUI(std::vector<Coat> _coats, QWidget* parent) : QWidget{ parent }, coats{ _coats }
{
	this->initGUI();
	this->connectSignalsAndSlots();
	this->populateCoatsList();
	this->repo = new Repository;
	this->serv = new Service(*repo);
}

CoatsGUI::~CoatsGUI()
{
}

void CoatsGUI::initGUI()
{
	//General layout of the window
	QHBoxLayout* layout = new QHBoxLayout{ this };

	// left side - just the list
	this->coatsList = new QListWidget{};
	// set the selection model
	this->coatsList->setSelectionMode(QAbstractItemView::SingleSelection);
	layout->addWidget(this->coatsList);

	// right side - coat information + buttons
	QWidget* rightSide = new QWidget{};
	QVBoxLayout* vLayout = new QVBoxLayout{ rightSide };

	// coat information
	QWidget* coatDataWidget = new QWidget{};
	QFormLayout* formLayout = new QFormLayout{ coatDataWidget };
	this->sizeSpinBox = new QSpinBox{};
	this->colourEdit = new QLineEdit{};
	this->priceSpinBox = new QDoubleSpinBox{};
	this->quantitySpinBox = new QSpinBox{};
	this->photographEdit = new QTextEdit{};
	QFont f{ "Times New Roman", 16 };
	QLabel* sizeLabel = new QLabel{ "&Coat size:" };
	sizeLabel->setBuddy(this->sizeSpinBox);
	QLabel* colourLabel = new QLabel{ "&Coat colour : " };
	colourLabel->setBuddy(this->colourEdit);
	QLabel* priceLabel = new QLabel{ "&Coat price : " };
	priceLabel->setBuddy(this->priceSpinBox);
	QLabel* quantityLabel = new QLabel{ "&Coat quantity : " };
	quantityLabel->setBuddy(this->quantitySpinBox);
	QLabel* photographLabel = new QLabel{ "&Photograph:" };
	photographLabel->setBuddy(this->photographEdit);
	sizeLabel->setFont(f);
	colourLabel->setFont(f);
	priceLabel->setFont(f);
	quantityLabel->setFont(f);
	photographLabel->setFont(f);
	this->sizeSpinBox->setFont(f);
	this->sizeSpinBox->setRange(20, 80);
	this->colourEdit->setFont(f);
	this->priceSpinBox->setFont(f);
	this->priceSpinBox->setRange(9.99, 1999.99);
	this->quantitySpinBox->setFont(f);
	this->quantitySpinBox->setRange(1, 100);
	this->photographEdit->setFont(f);
	formLayout->addRow(sizeLabel, this->sizeSpinBox);
	formLayout->addRow(colourLabel, this->colourEdit);
	formLayout->addRow(priceLabel, this->priceSpinBox);
	formLayout->addRow(quantityLabel, this->quantitySpinBox);
	formLayout->addRow(photographLabel, this->photographEdit);

	vLayout->addWidget(coatDataWidget);

	// buttons
	QWidget* buttonsWidget = new QWidget{};
	QHBoxLayout* hLayout = new QHBoxLayout{ buttonsWidget };
	this->addCoatButton = new QPushButton("Add Coat");
	this->addCoatButton->setFont(f);
	this->deleteCoatButton = new QPushButton("Delete Coat");
	this->deleteCoatButton->setFont(f);
	this->updateCoatButton = new QPushButton("Update Coat");
	this->updateCoatButton->setFont(f);
	this->undoButton = new QPushButton("Undo");
	this->undoButton->setFont(f);
	this->redoButton = new QPushButton("Redo");
	this->redoButton->setFont(f);
	hLayout->addWidget(this->addCoatButton);
	hLayout->addWidget(this->deleteCoatButton);
	hLayout->addWidget(this->updateCoatButton);
	hLayout->addWidget(this->undoButton);
	hLayout->addWidget(this->redoButton);

	vLayout->addWidget(buttonsWidget);

	//shortcuts
	this->undoShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Z), this);
	this->redoShortcut = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_Y), this);

	// add everything to the big layout
	layout->addWidget(this->coatsList);
	layout->addWidget(rightSide);
}

void CoatsGUI::connectSignalsAndSlots()
{
	// when the vector of coats is updated - re-populate the list
	QObject::connect(this, &CoatsGUI::coatsUpdatedSignal, this, &CoatsGUI::populateCoatsList);

	// add a connection: function listItemChanged() will be called when an item in the list is selected
	QObject::connect(this->coatsList, &QListWidget::itemSelectionChanged, this, [this]() {this->listItemChanged(); });

	// add button connections
	QObject::connect(this->addCoatButton, &QPushButton::clicked, this, &CoatsGUI::addCoatButtonHandler);
	QObject::connect(this->deleteCoatButton, &QPushButton::clicked, this, &CoatsGUI::deleteCoatButtonHandler);
	QObject::connect(this->updateCoatButton, &QPushButton::clicked, this, &CoatsGUI::updateCoatButtonHandler);
	QObject::connect(this->undoButton, &QPushButton::clicked, this, &CoatsGUI::undoButtonHandler);
	QObject::connect(this->redoButton, &QPushButton::clicked, this, &CoatsGUI::redoButtonHandler);

	// add connections for the shortcuts
	QObject::connect(this->undoShortcut, &QShortcut::activated, this, &CoatsGUI::undoButtonHandler);
	QObject::connect(this->redoShortcut, &QShortcut::activated, this, &CoatsGUI::redoButtonHandler);

	// connect the addCoat signal to the addCoat slot, which adds a gene to vector
	QObject::connect(this, SIGNAL(addCoatSignal(const int &, const string &, const double &, const int &, const string &)),
		this, SLOT(addCoat(const int&, const string&, const double&, const int&, const string&)));

	// connect the updateCoat signal to the updateCoat slot, which updates a gene in the vector
	QObject::connect(this, SIGNAL(updateCoatSignal(const int &, const string &, const double &, const int &, const string &)),
		this, SLOT(updateCoat(const int&, const string&, const double&, const int&, const string&)));
}

void CoatsGUI::addCoat(const int& size, const string& colour, const double& price, const int& quantity, const string& photograph)
{
	this->coats.push_back(Coat{ size,colour,price,quantity,photograph });

	// emit the signal: the coats were updated
	emit coatsUpdatedSignal();
}

void CoatsGUI::updateCoat(const int& size, const string& colour, const double& price, const int& quantity, const string& photograph)
{
	int idx = this->getSelectedIndex();

	if (idx < 0 || idx >= this->coats.size())
		return;

	this->coats[idx] = Coat{ size,colour,price,quantity,photograph };

	// emit the signal: the coats were updated
	emit coatsUpdatedSignal();
}

void CoatsGUI::addCoatButtonHandler()
{
	// read data from the textboxes and add the new coat
	int size = this->sizeSpinBox->value();
	QString colour = this->colourEdit->text();
	double price = this->priceSpinBox->value();
	int quantity = this->quantitySpinBox->value();
	QString photograph = this->photographEdit->toPlainText();

	this->serv->add(size, colour.toStdString(), price, quantity, photograph.toStdString());

	// emit the addCoat signal
	emit addCoatSignal(size,colour.toStdString(),price,quantity,photograph.toStdString());
}

void CoatsGUI::deleteCoatButtonHandler()
{
	// get the selected index and delete the coat
	int idx = this->getSelectedIndex();

	if (idx < 0 || idx >= this->coats.size())
		return;

	this->coats.erase(this->coats.begin() + idx);
	this->serv->remove(idx);

	// emit the signal: the coats were updated
	emit coatsUpdatedSignal();
}

void CoatsGUI::updateCoatButtonHandler()
{
	int idx = this->getSelectedIndex();

	if (idx < 0 || idx >= this->coats.size())
		return;

	int size = this->sizeSpinBox->value();
	QString colour = this->colourEdit->text();
	double price = this->priceSpinBox->value();
	int quantity = this->quantitySpinBox->value();
	QString photograph = this->photographEdit->toPlainText();
	
	this->serv->update(size, colour.toStdString(), price, quantity, photograph.toStdString(),idx);

	emit updateCoatSignal(size, colour.toStdString(), price, quantity, photograph.toStdString());
	emit coatsUpdatedSignal();
}

void CoatsGUI::undoButtonHandler()
{
    this->serv->undo();
    this->coats = this->serv->getAll(); // Add this line
    // emit the signal: the coats were updated
    emit coatsUpdatedSignal();
}

void CoatsGUI::redoButtonHandler()
{
    this->serv->redo();
    this->coats = this->serv->getAll(); // Add this line
    // emit the signal: the coats were updated
    emit coatsUpdatedSignal();
}

void CoatsGUI::populateCoatsList()
{
	// clear the list, if there are elements in it
	if (this->coatsList->count() > 0)
		this->coatsList->clear();

	for (auto c : this->coats)
	{
		QString itemInList = QString::fromStdString(c.toString());
		QFont f{ "Verdana", 15 };
		QListWidgetItem* item = new QListWidgetItem{ itemInList };
		item->setFont(f);
		this->coatsList->addItem(item);
	}

	// set the selection on the first item in the list
	if (this->coats.size() > 0)
		this->coatsList->setCurrentRow(0);
}

int CoatsGUI::getSelectedIndex()
{
	if (this->coatsList->count() == 0)
		return -1;

	// get selected index
	QModelIndexList index = this->coatsList->selectionModel()->selectedIndexes();
	if (index.size() == 0)
	{
		this->sizeSpinBox->clear();
		this->colourEdit->clear();
		this->priceSpinBox->clear();
		this->quantitySpinBox->clear();
		this->photographEdit->clear();
		return -1;
	}

	int idx = index.at(0).row();
	return idx;
}

void CoatsGUI::listItemChanged()
{
	int idx = this->getSelectedIndex();
	if (idx == -1)
		return;

	// get the song at the selected index
	if (idx >= this->coats.size())
		return;
	Coat c = this->coats[idx];

	this->sizeSpinBox->setValue(c.getSize());
	this->colourEdit->setText(QString::fromStdString(c.getColour()));
	this->priceSpinBox->setValue(c.getPrice());
	this->quantitySpinBox->setValue(c.getQuantity());
	this->photographEdit->setText(QString::fromStdString(c.getPhotograph()));
}
