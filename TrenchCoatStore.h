#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TrenchCoatStore.h"

class TrenchCoatStore : public QMainWindow
{
    Q_OBJECT

public:
    TrenchCoatStore(QWidget *parent = nullptr);
    ~TrenchCoatStore();

private:
    Ui::TrenchCoatStoreClass ui;
};
