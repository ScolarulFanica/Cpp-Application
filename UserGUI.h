#pragma once
#include <qwidget.h>
#include "TrenchCoat.h"
#include "Service.h"
#include "ShoppingBasket.h"
#include "Repository.h"
#include <QListWidget>
#include <QFormLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QDir>
#include <QPixmap>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QVBoxLayout>
#include <QImage>
#include <QTableView>
#include "ImageUtil.h"

/*
Show the contents of the adoption list / movie watch list / shopping basket / tutorial watch list using a table view.
You must use the Qt View/Model components (QTableView). Create your own model – a class which inherits from QAbstractTableModel.
This window will be opened from your GUI's main window.
*/

class ShoppingBasketGUI : public QAbstractTableModel
{
    Q_OBJECT;
public slots:
	void updateModel()
	{
		updateData(repo.getAll());
	}
private:
    std::vector<Coat> coats;
    Repository repo;

public:
    ShoppingBasketGUI(Repository& repo) : repo{ repo } {}

    // Add the necessary QAbstractTableModel functions
    int rowCount(const QModelIndex& parent = QModelIndex{}) const override
    {
        return coats.size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex{}) const override
    {
        return 5; // Assuming you have 5 columns
    }

	void updateData(const std::vector<Coat>& newCoats)
	{
		beginResetModel();
		coats = newCoats;
		endResetModel();
	}

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override
    {
        int row = index.row();
        int column = index.column();
        Coat coat = coats[row];
        if (role == Qt::DisplayRole)
        {
            switch (column)
            {
            case 0:
                return QString::number(coat.getSize());
            case 1:
                return QString::fromStdString(coat.getColour());
            case 2:
                return QString::number(coat.getPrice());
            case 3:
                return QString::number(coat.getQuantity());
            case 4:
                return QString::fromStdString(coat.getPhotograph());
            default:
                break;
            }
        }
        return QVariant{};
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override
    {
        if (role == Qt::DisplayRole)
        {
            if (orientation == Qt::Horizontal)
            {
                switch (section)
                {
                case 0:
                    return "Size";
                case 1:
                    return "Colour";
                case 2:
                    return "Price";
                case 3:
                    return "Quantity";
                case 4:
                    return "Photograph";
                default:
                    break;
                }
            }
        }
        return QVariant{};
    }

    // Existing ShoppingBasket functions
    void add(const Coat& c)
    {
        coats.push_back(c);
        // Notify the view that the model has changed
        emit dataChanged(createIndex(coats.size() - 1, 0), createIndex(coats.size() - 1, 4));
    }

    std::vector<Coat> getAll() const
    {
        return coats;
    }
};


class UserGUI : public QWidget
{
	Q_OBJECT;

private:
	Repository repo = Repository();
	ShoppingBasket* shoppingBasket = new ShoppingBasket(repo);
	std::vector<Coat> coats;

	QPushButton* addCoatToBasketButton = new QPushButton("Add Coat");
	QPushButton* nextButton = new QPushButton("Next Coat");
	QPushButton* iterButton = new QPushButton("Iterate Coats");
	QPushButton* displayButton = new QPushButton("See shopping basket");

	QLabel* sizeLabel = new QLabel("Size: ");
	QLabel* colourLabel = new QLabel("Colour: ");
	QLabel* priceLabel = new QLabel("Price: ");
	QLabel* quantityLabel = new QLabel("Quantity: ");
	QLabel* photographLabel = new QLabel("Photograph: ");

	QLineEdit* sizeEdit = new QLineEdit();
	QLineEdit* colourEdit = new QLineEdit();
	QLineEdit* priceEdit = new QLineEdit();
	QLineEdit* quantityEdit = new QLineEdit();
	QLabel* image = new QLabel();

	int total = 0;
	QLabel* totalLabel = new QLabel("Total sum: ");

	QLineEdit* totalEdit = new QLineEdit();

	QVBoxLayout* mainLayout;
	QVBoxLayout* iterLayout;
	QVBoxLayout* shoppingBasketLayout;

	QWidget* Iterate = new QWidget();

	int currentCoat = 0;

	QNetworkAccessManager* manager = new QNetworkAccessManager();

	QTableView* ShoppingBasketView = new QTableView();
signals:
	void coatAdded();
	
public:
	UserGUI()
	{
		shoppingBasket = new ShoppingBasket(repo);
		this->setWindowTitle("User UI");

		mainLayout = new QVBoxLayout();

		iterLayout = new QVBoxLayout();

		shoppingBasketLayout = new QVBoxLayout();

		iterLayout->addWidget(sizeLabel);
		iterLayout->addWidget(sizeEdit);
		iterLayout->addWidget(colourLabel);
		iterLayout->addWidget(colourEdit);
		iterLayout->addWidget(priceLabel);
		iterLayout->addWidget(priceEdit);
		iterLayout->addWidget(quantityLabel);
		iterLayout->addWidget(quantityEdit);
		iterLayout->addWidget(photographLabel);
		iterLayout->addWidget(image);
		iterLayout->addWidget(nextButton);
		iterLayout->addWidget(addCoatToBasketButton);

		totalEdit->setText(QString::number(0));

		ShoppingBasketGUI* model = new ShoppingBasketGUI(repo);
		ShoppingBasketView->setModel(model);

    	connect(this, &UserGUI::coatAdded, model, &ShoppingBasketGUI::updateModel);

		sizeEdit->setReadOnly(true);
		colourEdit->setReadOnly(true);
		priceEdit->setReadOnly(true);
		quantityEdit->setReadOnly(true);
		totalEdit->setReadOnly(true);

		mainLayout->addWidget(iterButton);
		mainLayout->addWidget(displayButton);
		mainLayout->addWidget(totalLabel);
		mainLayout->addWidget(totalEdit);

		Iterate->setLayout(iterLayout);

		QObject::connect(iterButton, &QPushButton::clicked, [this]() {on_iter(); });
		QObject::connect(nextButton, &QPushButton::clicked, [this]() {on_next(); });
		QObject::connect(addCoatToBasketButton, &QPushButton::clicked, [this]() {on_add(); });
		QObject::connect(displayButton, &QPushButton::clicked, [this]()
			{
				dynamic_cast<ShoppingBasketGUI*>(ShoppingBasketView->model())->updateData(shoppingBasket->getAll());
				ShoppingBasketView->show();
				 });

			this->setLayout(mainLayout);
			this->show();
		}

public:
	~UserGUI()
	{
		delete shoppingBasket;
	}

	void on_add()
	{
		shoppingBasket->add(coats[currentCoat]);
		total += coats[currentCoat].getPrice();
		totalEdit->setText(QString::number(total));
		coats[currentCoat].setQuantity(coats[currentCoat].getQuantity()-1);

		emit coatAdded();
	}

	void on_next()
	{
		currentCoat++;
		if (currentCoat >= coats.size())
		{
			currentCoat = 0;
		}
		sizeEdit->setText(QString::number(coats[currentCoat].getSize()));
		colourEdit->setText(QString::fromStdString(coats[currentCoat].getColour()));
		priceEdit->setText(QString::number(coats[currentCoat].getPrice()));
		quantityEdit->setText(QString::number(coats[currentCoat].getQuantity()));
		ImageUtil* imageUtil = new ImageUtil();
		imageUtil->loadFromUrl(QUrl(QString::fromStdString(coats[currentCoat].getPhotograph())));
		imageUtil->connect(imageUtil, &ImageUtil::loaded, [=]() {
			this->image->setPixmap(QPixmap::fromImage(imageUtil->image()));
			this->image->setScaledContents(true);
			this->image->setMaximumSize(200, 200);
			});
	}

	void on_iter()
	{
		coats = repo.getAll();
		currentCoat = 0;

		sizeEdit->setText(QString::number(coats[currentCoat].getSize()));
		colourEdit->setText(QString::fromStdString(coats[currentCoat].getColour()));
		priceEdit->setText(QString::number(coats[currentCoat].getPrice()));
		quantityEdit->setText(QString::number(coats[currentCoat].getQuantity()));
		ImageUtil* imageUtil = new ImageUtil();
		imageUtil->loadFromUrl(QUrl(QString::fromStdString(coats[currentCoat].getPhotograph())));
		imageUtil->connect(imageUtil, &ImageUtil::loaded, [=]() {
			this->image->setPixmap(QPixmap::fromImage(imageUtil->image()));
			this->image->setScaledContents(true);
			this->image->setMaximumSize(200, 200);
			});
		this->Iterate->show();
	}

	ShoppingBasket* getShoppingBasket()
	{
		return shoppingBasket;
	}

};