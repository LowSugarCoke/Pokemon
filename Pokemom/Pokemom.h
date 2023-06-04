#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Pokemom.h"

class Pokemom : public QMainWindow
{
	Q_OBJECT

public:
	Pokemom(QWidget *parent = Q_NULLPTR);

private:
	Ui::PokemomClass ui;
};
