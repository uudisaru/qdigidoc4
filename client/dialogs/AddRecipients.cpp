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

using namespace ria::qdigidoc4;

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

	connect( ui->confirm, &LabelButton::clicked, this, &AddRecipients::accept );
	connect( ui->cancel, &LabelButton::clicked, this, &AddRecipients::reject );
	connect( this, &AddRecipients::finished, this, &AddRecipients::close );


	ui->toAdd->init( ItemList::Address, "Adressaatide lisamine" );
	AddressItem *add1 = new AddressItem(UnsignedContainer, 0);
	add1->update( "Aadu Aamer", "34511114231", "ID-kaat", 2 );
	ui->toAdd->addWidget( add1 );
	AddressItem *add2 = new AddressItem(UnsignedContainer, 0);
	add2->update( "Alma Tamm", "44510104561", "Digi-ID", 3 );
	ui->toAdd->addWidget( add2 );

	ui->added->init( ItemList::Address, "Lisatud adressaadid" );

	AddressItem *curr1 = new AddressItem(UnsignedContainer, 0);
	curr1->update( "Heino Liin", "34664778636", "ID-kaat", 1 );
	ui->added->addWidget( curr1 );
	AddressItem *curr2 = new AddressItem(UnsignedContainer, 0);
	curr2->update( "Vello Karm", "44510104561", "ID-kaat", 1 );
	ui->added->addWidget( curr2 );
	AddressItem *curr3 = new AddressItem(UnsignedContainer, 0);
	curr3->update( "Ivar Tuisk", "45643644331", "Digi-ID", 1 );
	ui->added->addWidget( curr3 );

	ui->fromCard->init( LabelButton::DeepCerulean, "LISA SERTIFIKAAT KAARTILT", 101 );
	ui->fromFile->init( LabelButton::DeepCerulean, "LISA SERTIFIKAAT FAILIST", 103 );
	ui->fromHistory->init( LabelButton::DeepCerulean, "VIIMATI LISATUD", 107 );

	ui->cancel->init( LabelButton::WhiteForeground | LabelButton::RedBackground, "KATKESTA", 111 );
	ui->confirm->init( LabelButton::WhiteForeground | LabelButton::BlueBackground, "KINNITA", 113 );
}

int AddRecipients::exec()
{
	Overlay overlay(parentWidget());
	overlay.show();
	auto rc = QDialog::exec();
	overlay.close();

	return rc;
}
