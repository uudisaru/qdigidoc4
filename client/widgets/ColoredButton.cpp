#include "ColoredButton.h"

#include <QMouseEvent>
#include "Styles.h"


ColoredButton::ColoredButton(QWidget *parent) :
	QLabel(parent),
	style(Common),
	state(Normal),
	enabled(true)
{
}

ColoredButton::~ColoredButton()
{
}


void ColoredButton::init(ButtonStyle style, bool enabled, const QString &text)
{
	this->style = style;
	this->enabled = enabled;
	if(style == Main ||style == Light ||style == Red)
		setFont( Styles::font( Styles::Condensed, 14 ) );
	else
		setFont( Styles::font( Styles::Condensed, 12 ) );
	if(!text.isEmpty())
		setText(text);

	setEnabled(enabled);
}

void ColoredButton::setEnabled(bool enabled)
{
	this->enabled = enabled;
	this->state = enabled? Normal : Disabled;
	update();
}

void ColoredButton::enterEvent( QEvent */*event*/ )
{
	if(enabled)
	{
		state = Hover;
		update();
	}
}

void ColoredButton::leaveEvent( QEvent */*event*/ )
{
	if(enabled)
	{
		state = Normal;
		update();
	}
}

void ColoredButton::mousePressEvent(QMouseEvent */*event*/)
{
	if(enabled)
	{
		state = Down;
		update();
	}
}

void ColoredButton::mouseReleaseEvent(QMouseEvent */*event*/)
{
	if(enabled)
	{
		if(state == Down)
			emit clicked();
		state = Hover;
		update();
	}
}

void ColoredButton::mouseMoveEvent(QMouseEvent *event)
{
	if(enabled)
	{
		if(event->pos().x() < 0 || event->pos().x() > width() || event->pos().y() < 0 || event->pos().y() > height())
		{
			state = Normal;
			update();
		}
		else
		{
			state = Down;
			update();
		}
	}
}

void ColoredButton::update()
{
	const char *styleCheet[5][4] =
		{
			// Main
			{	"color: #ffffff;  border: none;  border-radius: 2px;  background-color: #006EB5;",  // Normal
				"color: #ffffff;  border: none;  border-radius: 2px;  background-color: #008DCF;",  // Hover
				"color: #ffffff;  border: none;  border-radius: 2px;  background-color: #41B6E6;",  // Down
				"color: #ffffff;  border: none;  border-radius: 2px;  background-color: #bedbed;"   // Disabled
			},

			// Light
			{	"color: #006EB5;  border: 1px solid #006EB5;  border-radius: 2px;",                 // Normal
				"color: #008DCF;  border: 1px solid #008DCF;  border-radius: 2px;",                 // Hover
				"color: #ffffff;  border: none;  border-radius: 2px;  background-color: #006EB5;",  // Down
				""                                                                                  // Disabled
			},

			// Red
			{	"color: #ffffff;  border: none;  border-radius: 2px;  background-color: #981E32;",  // Normal
				"color: #ffffff;  border: none;  border-radius: 2px;  background-color: #CD2541;",  // Hover
				"color: #ffffff;  border: none;  border-radius: 2px;  background-color: #F24A66;",  // Down
				""                                                                                  // Disabled
			},

			// Negative
			{	"color: #981E32;  border: none;",                                                   // Normal
				"color: #981E32;  border: 1px solid #981E32;  border-radius: 2px;",                 // Hover
				"color: #ffffff;  border: none;  border-radius: 2px;  background-color: #981E32;",  // Down
				""                                                                                  // Disabled
			},

			// Common
			{	"color: #006EB5;  border: none;",                                                   // Normal
				"color: #006EB5;  border: 1px solid #006EB5;  border-radius: 2px;",                 // Hover
				"color: #ffffff;  border: none;  border-radius: 2px;  background-color: #006EB5;",  // Down
				"color: #75787B;  border: none;"                                                    // Disabled
			},
		};

	setStyleSheet(styleCheet[style][state]);
}
