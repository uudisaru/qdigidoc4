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

#include "ItemList.h"
#include "ui_ItemList.h"
#include "Styles.h"
#include "widgets/AddressItem.h"
#include "widgets/FileItem.h"
#include "widgets/SignatureItem.h"

#include <vector>
#include <QLayoutItem>

using namespace ria::qdigidoc4;

ItemList::ItemList(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ItemList)
{
	ui->setupUi(this);

	connect(ui->add, &LabelButton::clicked, this, &ItemList::add);
}

ItemList::~ItemList()
{
	delete ui;
}

void ItemList::add(int code)
{
	StyledWidget* item;
	if (code == FileAdd)
	{
		item = new FileItem(state);
	} 
	else if (code == SignatureAdd)
	{
		item = new SignatureItem(state);
	}
	else
	{
		item = new AddressItem(state);
	}
	ui->itemLayout->insertWidget(items.size(), item);
	item->show();
	items.push_back(item);

	if(code != SignatureAdd)  // !!! Et SignatureAdd ei läheks lõpmatusse tsüklisse.
		emit addItem( code );
}

void ItemList::addWidget(StyledWidget *widget)
{
	ui->itemLayout->insertWidget(items.size(), widget);
	widget->show();
	items.push_back(widget);

	//emit addItem( code );
}

QString ItemList::addLabel() const
{
	switch(itemType)
	{
	case File: return "+ LISA VEEL FAILE";
	case Address: return "+ LISA ADRESSAAT";
	case All: return "+ LISA KÕIK";
	default: return "";
	}
}

QString ItemList::anchor() const
{
	switch(itemType)
	{
	case File: return "#add-file";
	case Address: return "#add-address";
	default: return "";
	}
}

void ItemList::clear()
{
	StyledWidget* widget;
	auto it = items.begin();
	while (it != items.end()) {
		widget = *it;
		it = items.erase(it);
		widget->close();
		delete widget;
	}
}

void ItemList::init( ItemType item, const QString &header)
{
	itemType = item;
	ui->listHeader->setText(header);
	ui->listHeader->setFont( Styles::font(Styles::Regular, 20));
	if (item == Signature)
	{
		ui->add->hide();
	} 
	else
	{
		ui->add->init(LabelButton::DeepCerulean | LabelButton::WhiteBackground, addLabel(), itemType == File ? FileAdd : AddressAdd);
	}
}

void ItemList::setAddLabel(bool visible, const QString &label)
{
	ui->add->setText(label);
	ui->add->setAlignment(Qt::AlignCenter | Qt::AlignRight);
	if(visible)
	{
		ui->add->show();
	}
	else
	{
		ui->add->hide();
	}
}

void ItemList::stateChange(ContainerState state)
{
	this->state = state;
	if (state & (UnsignedContainer | UnsignedSavedContainer | UnencryptedContainer) )
	{
		ui->add->show();
	}
	else
	{
		ui->add->hide();
	}

	for(auto item: items)
	{
		item->stateChange(state);
	}
}
