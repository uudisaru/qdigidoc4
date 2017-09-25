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

#pragma once

#include <QLabel>

namespace Ui {
class ColoredButton;
}

class ColoredButton : public QLabel
{
    Q_OBJECT

public:
	enum ButtonStyle
	{
		Main,
		Light,
		Red,
		Negative,
		Common
	};

	enum ButtonState
	{
		Normal,
		Hover,
		Down,
		Disabled
	};



    explicit ColoredButton(QWidget *parent = 0);
    ~ColoredButton();

	void init(ButtonStyle style = Common, bool enabled = true, const QString &text = "");
	void setEnabled(bool enabled);

signals:
	void clicked();

protected:
	void enterEvent( QEvent *event ) override;
	void leaveEvent( QEvent *event ) override;
	void mousePressEvent(QMouseEvent *event) override;
	void mouseReleaseEvent(QMouseEvent *event) override;
	void mouseMoveEvent(QMouseEvent *event) override;
	void update();

private:
    Ui::ColoredButton *ui;

	ButtonStyle style;
	ButtonState state;
	bool enabled;
};
