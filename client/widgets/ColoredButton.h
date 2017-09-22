#ifndef COLOREDBUTTON_H
#define COLOREDBUTTON_H

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

#endif // COLOREDBUTTON_H
