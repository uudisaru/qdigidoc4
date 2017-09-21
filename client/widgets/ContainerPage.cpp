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

#include "ContainerPage.h"
#include "ui_ContainerPage.h"
#include "Styles.h"

#include <QGraphicsDropShadowEffect>

using namespace ria::qdigidoc4;

#define ACTION_WIDTH 200
#define ACTION_HEIGHT 65

ContainerPage::ContainerPage( QWidget *parent ) :
	QWidget( parent ),
	ui( new Ui::ContainerPage )
{
	ui->setupUi( this );
	init();
}

ContainerPage::~ContainerPage()
{
	delete ui;
}

void ContainerPage::init()
{
	static const QString style = "QLabel { padding: 6px 10px; border-top-left-radius: 3px; border-bottom-left-radius: 3px; background-color: %1; color: #ffffff; border: none; text-decoration: none solid; }";
	static const QString link = "<a href=\"#mainAction\" style=\"background-color: %1; color: #ffffff; text-decoration: none solid;\">Allkirjasta ID-Kaardiga</a>";
	
	ui->leftPane->init( ItemList::File, "Kontaineri failid" );

	QFont regular = Styles::font( Styles::Regular, 14 );
	ui->warningText->setFont( regular );
	ui->warningAction->setFont( Styles::font( Styles::Regular, 14, QFont::Bold ) );
	QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect();
	shadow->setColor( QColor( 233, 200, 143 ) );
	shadow->setXOffset( 4 );
	shadow->setYOffset( 4 );
	ui->warning->setGraphicsEffect( shadow );
	ui->containerHeader->setGraphicsEffect( shadow );

	ui->container->setFont( regular );
	ui->containerFile->setFont( regular );
	ui->changeLocation->setIcons( "/images/edit_dark.svg", "/images/edit_light.svg", 3, 3, 19, 19 );
	ui->changeLocation->init( LabelButton::DeepCerulean | LabelButton::PorcelainBackground, "MUUDA", Actions::ContainerLocation );
	ui->cancel->init( LabelButton::Mojo, "← KATKESTA", Actions::ContainerCancel );
	ui->encrypt->init( LabelButton::DeepCerulean, "KRÜPTEERI", Actions::ContainerEncrypt );
	ui->navigateToContainer->init( LabelButton::DeepCerulean, "AVA KONTAINERI ASUKOHT", Actions::ContainerNavigate );
	ui->email->init( LabelButton::DeepCerulean, "EDASTA E-MAILIGA", Actions::ContainerEmail );
	ui->save->init( LabelButton::DeepCerulean, "SALVESTA ALLKIRJASTAMATA", Actions::ContainerSave );

	connect( ui->cancel, &LabelButton::clicked, this, &ContainerPage::action );
//	connect( ui->leftPane, &ItemList::addItem, this, &ContainerPage::action );
	connect( ui->rightPane, &ItemList::addItem, this, &ContainerPage::action );
}

void ContainerPage::transition( ContainerState state )
{
	ui->leftPane->stateChange( state );
	ui->rightPane->stateChange( state );

	switch( state )
	{
	case UnsignedContainer:
		ui->leftPane->clear();
		ui->rightPane->clear();
		hideRightPane();
		ui->leftPane->init( ItemList::File, "Allkirjastamiseks valitud failid" );
		showMainAction( SignatureAdd, "ALLKIRJASTA\nID-KAARDIGA" );
		showButtons( { ui->cancel, ui->save } );
		hideButtons( { ui->encrypt, ui->navigateToContainer, ui->email } );
		break;
	case UnsignedSavedContainer:
		break;
	case SignedContainer:
		ui->leftPane->init( ItemList::File, "Kontaineri failid" );
		showRightPane( ItemList::Signature, "Kontaineri allkirjad" );
		ui->rightPane->add( SignatureAdd );
		hideMainAction();
		hideButtons( { ui->cancel, ui->save } );
		showButtons( { ui->encrypt, ui->navigateToContainer, ui->email } );
		break;
	case UnencryptedContainer:
		ui->leftPane->clear();
		ui->rightPane->clear();
		ui->leftPane->init( ItemList::File, "Krüpteerimiseks valitud failid" );
		showRightPane( ItemList::Address, "Adressaadid" );
		showMainAction( EncryptContainer, "KRÜPTEERI" );
		showButtons( { ui->cancel } );
		hideButtons( { ui->encrypt, ui->save, ui->navigateToContainer, ui->email } );
		break;
	case EncryptedContainer:
		ui->leftPane->init( ItemList::File, "Krüpteeritud failid" );
		showRightPane( ItemList::Address, "Adressaadid" );
		hideMainAction();
		hideButtons( { ui->encrypt, ui->cancel, ui->save } );
		showButtons( { ui->navigateToContainer, ui->email } );
		break;
	case DecryptedContainer:
		break;
	}
}

void ContainerPage::hideButtons( std::vector<QWidget*> buttons )
{
	for( auto *button: buttons ) button->hide();
}

void ContainerPage::hideMainAction()
{
	if( mainAction )
	{
		mainAction->hide();
	}
	ui->mainActionSpacer->changeSize( 1, 20, QSizePolicy::Fixed );
}

void ContainerPage::hideRightPane()
{
	ui->rightPane->hide();
}

void ContainerPage::hideWarningArea()
{
	ui->warning->hide();
}

void ContainerPage::showButtons( std::vector<QWidget*> buttons )
{
	for( auto *button: buttons ) button->show();
}

void ContainerPage::showRightPane( ItemList::ItemType itemType, const QString &header )
{
	ui->rightPane->init( itemType, header );
	ui->rightPane->show();
}

void ContainerPage::showWarningText( const QString &text, const QString &link )
{
	ui->warning->show();
	ui->warningText->setText( text );
	ui->warningAction->setText( link );
	ui->warningAction->setTextFormat( Qt::RichText );
	ui->warningAction->setTextInteractionFlags( Qt::TextBrowserInteraction );
	ui->warningAction->setOpenExternalLinks( true );	
}

void ContainerPage::showMainAction( Actions action, const QString &label )
{
	if( mainAction )
	{
		mainAction->update( action, label, action == SignatureAdd );
		mainAction->show();
	}
	else
	{
		mainAction.reset( new MainAction( action, label, this, action == SignatureAdd ) );
		mainAction->move( this->width() - ACTION_WIDTH, this->height() - ACTION_HEIGHT );
		connect( mainAction.get(), &MainAction::action, this, &ContainerPage::action );
		mainAction->show();
	}
	ui->mainActionSpacer->changeSize( 198, 20, QSizePolicy::Fixed );	
}

// Mouse click on warning region will hide it.
void ContainerPage::mousePressEvent ( QMouseEvent * event )
{
	if( ui->warning->underMouse() )
		hideWarningArea();
}

void ContainerPage::resizeEvent( QResizeEvent *event )
{
	if( mainAction )
	{
		mainAction->move( this->width() - ACTION_WIDTH, this->height() - ACTION_HEIGHT );
	}
}
