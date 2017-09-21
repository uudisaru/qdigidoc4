/*
 * QDigiDoc4
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */


#include "AddRecipients.h"
#include "ui_AddRecipients.h"
#include "Styles.h"
#include "effects/Overlay.h"

#include "common_enums.h"


AddRecipients::AddRecipients(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRecipients)
{
    init();
}

AddRecipients::~AddRecipients()
{
    delete ui;
}


void AddRecipients::init()
{
	ui->setupUi(this);
	setWindowFlags( Qt::Dialog | Qt::FramelessWindowHint );
	setWindowModality( Qt::ApplicationModal );

	ui->toAdd->init( ItemList::Signature, "Adressaatide lisamine" );
    ui->added->init( ItemList::Signature, "Lisatud adressaadid" );

	ui->fromCard->init( LabelButton::DeepCerulean, "LISA SERTIFIKAAT KAARTILT", 101 );
	ui->fromFile->init( LabelButton::DeepCerulean, "LISA SERTIFIKAAT FAILIST", 103 );
	ui->fromHistory->init( LabelButton::DeepCerulean, "VIIMATI LISATUD", 107 );
}

int AddRecipients::exec()
{
	Overlay overlay(parentWidget());
	overlay.show();
	auto rc = QDialog::exec();
	overlay.close();

	return rc;
}
