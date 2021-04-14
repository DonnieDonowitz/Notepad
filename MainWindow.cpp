#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
	ui(new Ui::MainWindowClass),
	editor(new QTextEdit),
	fileMenu(new QMenu(tr("&File"))),
	editMenu(new QMenu(tr("&Edit"))),
	format(new QToolBar(tr("Format")))
{
    ui->setupUi(this);
	setWindowTitle("CAM Notepad");
	setWindowIcon(QIcon("img/icon.png"));

	setupFileMenu();
	setupEditMenu();
	setupFormatToolbar();

	ui->menuBar->addMenu(fileMenu);
	ui->menuBar->addMenu(editMenu);
	ui->mainToolBar->addWidget(format);

	setCentralWidget(editor);

	QFont font;
	font.setFamily("Arial");
	editor->setFont(font);
}

MainWindow::~MainWindow()
{
	delete ui;
	delete editor;
	delete fileMenu;
	delete editMenu;
	delete format;
}

void MainWindow::onNewTriggered()
{
	currFile.clear();
	editor->setText(QString());
}

void MainWindow::onOpenTriggered() 
{
	QString filename = QFileDialog::getOpenFileName(this, "Open the file");
	QFile file(filename);
	currFile = filename;
	if (!file.open(QIODevice::ReadOnly | QFile::Text))
	{
		QMessageBox::warning(this, "Warning", "Error opening file: " + file.errorString());
		return;
	}
	setWindowTitle(filename);
	QTextStream in(&file);
	QString text = in.readAll();
	editor->setText(text);
	file.close();
}

void MainWindow::onSaveAsTriggered()
{
	QString filename = QFileDialog::getSaveFileName(this, "Save the file");
	QFile file(filename);
	currFile = filename;
	if (!file.open(QFile::WriteOnly | QFile::Text))
	{
		QMessageBox::warning(this, "Warning", "Error saving file: " + file.errorString());
		return;
	}
	setWindowTitle(filename);
	QTextStream out(&file);
	QString text = editor->toPlainText();
	out << text;
	out.flush();
	file.close();
}

void MainWindow::onPrintTriggered()
{
	QPrinter printer;
	printer.setPrinterName("Default Printer");
	QPrintDialog pDialog(&printer, this);
	if (pDialog.exec() == QPrintDialog::Rejected)
	{
		QMessageBox::warning(this, "Warning", "Connection failed to the printer");
		return;
	}
	editor->print(&printer);
}

void MainWindow::onBoldTriggered() 
{
	QList<QAction *> formatTypes = format->actions();
	if (formatTypes[0]->isChecked())
	{
		editor->setFontWeight(QFont::Bold);
	}
	else
	{
		editor->setFontWeight(QFont::Normal);
	}
}

void MainWindow::onItalicTriggered() 
{
	QList<QAction *> formatTypes = format->actions();
	editor->setFontItalic(formatTypes[1]->isChecked());
}

void MainWindow::onUnderlinedTriggered() 
{
	QList<QAction *> formatTypes = format->actions();
	editor->setFontUnderline(formatTypes[2]->isChecked());
}

void MainWindow::setupFileMenu()
{
	QAction* new_ = new QAction("&New", this);
	new_->setIcon(QIcon("img/new.png"));
	new_->setIconVisibleInMenu(true);
	new_->setShortcut(QKeySequence::New);
	new_->setShortcutVisibleInContextMenu(true);
	QObject::connect(new_, SIGNAL(triggered()), this, SLOT(onNewTriggered()));

	QAction* open_ = new QAction("&Open", this);
	open_->setIcon(QIcon("img/open.png"));
	open_->setIconVisibleInMenu(true);
	open_->setShortcut(QKeySequence::Open);
	open_->setShortcutVisibleInContextMenu(true);
	QObject::connect(open_, SIGNAL(triggered()), this, SLOT(onOpenTriggered()));

	QAction* saveAs = new QAction("&Save As", this);
	saveAs->setIcon(QIcon("img/save.png"));
	saveAs->setIconVisibleInMenu(true);
	saveAs->setShortcut(QKeySequence::Save);
	saveAs->setShortcutVisibleInContextMenu(true);
	QObject::connect(saveAs, SIGNAL(triggered()), this, SLOT(onSaveAsTriggered()));

	QAction* print_ = new QAction("&Print", this);
	print_->setIcon(QIcon("img/print.png"));
	print_->setIconVisibleInMenu(true);
	print_->setShortcut(QKeySequence::Print);
	print_->setShortcutVisibleInContextMenu(true);
	QObject::connect(print_, SIGNAL(triggered()), this, SLOT(onPrintTriggered()));

	QAction* exit_ = new QAction("&Exit", this);
	exit_->setIcon(QIcon("img/exit.png"));
	exit_->setIconVisibleInMenu(true);
	exit_->setShortcut(tr("CTRL+Q"));
	exit_->setShortcutVisibleInContextMenu(true);
	QObject::connect(exit_,&QAction::triggered, this, &QApplication::quit);

	fileMenu->addAction(new_);
	fileMenu->addAction(open_);
	fileMenu->addAction(saveAs);
	fileMenu->addSeparator();
	fileMenu->addAction(print_);
	fileMenu->addSeparator();
	fileMenu->addAction(exit_);
}

void MainWindow::setupEditMenu()
{
	QAction* copy = new QAction("&Copy", this);
	copy->setIcon(QIcon("img/copy.png"));
	copy->setIconVisibleInMenu(true);
	copy->setShortcut(QKeySequence::Copy);
	copy->setShortcutVisibleInContextMenu(true);
	QObject::connect(copy, &QAction::triggered, this->editor, &QTextEdit::copy);

	QAction* cut = new QAction("&Cut", this);
	cut->setIcon(QIcon("img/cut.png"));
	cut->setIconVisibleInMenu(true);
	cut->setShortcut(QKeySequence::Cut);
	cut->setShortcutVisibleInContextMenu(true);
	QObject::connect(cut, &QAction::triggered, this->editor, &QTextEdit::cut);

	QAction* paste = new QAction("&Paste", this);
	paste->setIcon(QIcon("img/paste.png"));
	paste->setIconVisibleInMenu(true);
	paste->setShortcut(QKeySequence::Paste);
	paste->setShortcutVisibleInContextMenu(true);
	QObject::connect(paste, &QAction::triggered, this->editor, &QTextEdit::paste);

	QAction* undo = new QAction("&Undo", this);
	undo->setIcon(QIcon("img/undo.png"));
	undo->setIconVisibleInMenu(true);
	undo->setShortcut(QKeySequence::Undo);
	undo->setShortcutVisibleInContextMenu(true);
	QObject::connect(undo, &QAction::triggered, this->editor, &QTextEdit::undo);

	QAction* redo = new QAction("&Redo", this);
	redo->setIcon(QIcon("img/redo.png"));
	redo->setIconVisibleInMenu(true);
	redo->setShortcut(QKeySequence::Redo);
	redo->setShortcutVisibleInContextMenu(true);
	QObject::connect(redo, &QAction::triggered, this->editor, &QTextEdit::redo);

	editMenu->addAction(copy);
	editMenu->addAction(cut);
	editMenu->addAction(paste);
	editMenu->addSeparator();
	editMenu->addAction(undo);
	editMenu->addAction(redo);
}

void MainWindow::setupFormatToolbar()
{
	QAction* bold = new QAction("&Bold", this);
	bold->setIcon(QIcon("img/bold.png"));
	bold->setIconVisibleInMenu(true);
	bold->setCheckable(true);
	bold->setShortcut(QKeySequence::Bold);
	QObject::connect(bold, SIGNAL(triggered()), this, SLOT(onBoldTriggered()));

	QAction* italic = new QAction("&Italic", this);
	italic->setIcon(QIcon("img/italic.png"));
	italic->setIconVisibleInMenu(true);
	italic->setCheckable(true);
	italic->setShortcut(QKeySequence::Italic);
	QObject::connect(italic, SIGNAL(triggered()), this, SLOT(onItalicTriggered()));

	QAction* underlined = new QAction("&Underlined", this);
	underlined->setIcon(QIcon("img/underline.png"));
	underlined->setIconVisibleInMenu(true);
	underlined->setCheckable(true);
	underlined->setShortcut(QKeySequence::Underline);
	QObject::connect(underlined, SIGNAL(triggered()), this, SLOT(onUnderlinedTriggered()));

	format->addAction(bold);
	format->addAction(italic);
	format->addAction(underlined);
}