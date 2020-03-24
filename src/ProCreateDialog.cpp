#include "ProCreateDialog.h"
#include "ui_ProCreateDialog.h"

#include "XESFramework.h"

#include <zipper/zipper.h>

ProCreateDialog::ProCreateDialog( QWidget * parent /*= nullptr */ )
	:QDialog( parent ), ui( new Ui::ProCreateDialog )
{
	ui->setupUi( this );

	LoadPackage();

	connect( ui->toolButton, &QToolButton::clicked, this, &ProCreateDialog::OnToolButton );
	connect( ui->pushButtonNo, &QToolButton::clicked, this, &ProCreateDialog::OnPushButtonNo );
	connect( ui->pushButtonYes, &QToolButton::clicked, this, &ProCreateDialog::OnPushButtonYes );
}

ProCreateDialog::~ProCreateDialog()
{
	delete ui;
}

const QString & ProCreateDialog::GetPath() const
{
	return _Path;
}

void ProCreateDialog::LoadPackage()
{

}

void ProCreateDialog::OnToolButton()
{
	auto str = QFileDialog::getExistingDirectory( this, tr( "Select Directory" ), "/home" );

	if( str != "" )
	{
		ui->lineEditFolder->setText( str );
	}
}

void ProCreateDialog::OnPushButtonYes()
{
	if( ui->lineEditName->text().isEmpty() )
	{
		QMessageBox::warning( this, tr( "warning" ), tr( "project name is empty!" ) );
		return;
	}
	if( ui->lineEditFolder->text().isEmpty() )
	{
		QMessageBox::warning( this, tr( "warning" ), tr( "project path is empty!" ) );
		return;
	}

	_Path = ui->lineEditFolder->text() + "/" + ui->lineEditName->text();

	if( CreateProject() )
	{
		accept();
	}
	else
	{
		_Path = "";
		QMessageBox::warning( this, tr( "warning" ), tr( "create project fail!" ) );
	}
}

void ProCreateDialog::OnPushButtonNo()
{
	reject();
}

bool ProCreateDialog::CreateProject()
{
	auto path = std::filesystem::path( _Path.toUtf8().toStdString() );

	std::error_code code;
	if( !std::filesystem::create_directory( path, code ) )
	{
		std::cout << path << " : " << code.message() << std::endl;
		return false;
	}
	if( !std::filesystem::create_directory( path / "assets", code ) )
	{
		std::cout << path / "assets" << " : " << code.message() << std::endl;
		return false;
	}
	if( !std::filesystem::create_directory( path / "data", code ) )
	{
		std::cout << path / "data" << " : " << code.message() << std::endl;
		return false;
	}
	if( !std::filesystem::create_directory( path / "modules", code ) )
	{
		std::cout << path / "modules" << " : " << code.message() << std::endl;
		return false;
	}
	if( !std::filesystem::create_directory( path / "plugins", code ) )
	{
		std::cout << path / "plugins" << " : " << code.message() << std::endl;
		return false;
	}
	if( !std::filesystem::create_directory( path / "source", code ) )
	{
		std::cout << path / "source" << " : " << code.message() << std::endl;
		return false;
	}


	std::ofstream proj( path / ( path.stem().u8string() + ".xeproj" ) );
	proj << "" << std::endl;
	proj.close();

	std::ofstream cmake( path / "source" / "CMakeLists.txt" );
	cmake << "" << std::endl;
	cmake.close();

	auto package_path = XE::XESFramework::GetCurrentFramework()->GetPackagePath();
	auto items = ui->listWidget->selectedItems();
	for( const auto & item : items )
	{
		auto path = package_path / item->data( Qt::UserRole + 1 ).toString().toUtf8().toStdString();
	}

	return true;
}
