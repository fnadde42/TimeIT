#ifndef EDITTASKDIALOG_H_
#define EDITTASKDIALOG_H_

#include "ParentChooser.h"
#include <gtkmm.h>
#include <string>
#include <vector>
#include <IEditTaskDialog.h>
#include <IAddTaskDIalog.h>
#include <IAutotrackAccessor.h>
#include <boost/shared_ptr.hpp>
#include <IWidget.h>
#include <Workspace.h>
#include <Database.h>

namespace GUI {
namespace Internal {

class EditTaskDialog: public Gtk::Dialog, public IEditTaskDialog, public IAddTaskDialog, public IWidget
{
public:
	EditTaskDialog( boost::shared_ptr<DB::Database>& database);
	virtual ~EditTaskDialog();
	void on_OKButton_clicked();
	void on_CancelButton_clicked();
	void on_data_changed();
	virtual void setTaskID(int64_t);
	virtual void setParent(int ID);
	virtual void show() { Gtk::Dialog::show(); }
	virtual void hide() { Gtk::Dialog::hide(); }
private:
	void createLayout();
	void check4changes();
	std::vector<int> getTickedWorkspaces();
	void setTickedWorkspaces(std::vector<int> workspaces);

	Gtk::Label NameLabel;
	Gtk::HBox hbox1;
	Gtk::HBox hbox2;
	Gtk::HBox hbox3;
	std::vector<Gtk::CheckButton*> checkbutton;
	Gtk::Table workspaceTable;
	Gtk::Label label1;
	Gtk::Frame DesktopFrame;
	Gtk::Table table2;
	Gtk::Button CancelButton;
	Gtk::Button OKButton;
	Gtk::Entry taskNameEntry;
	Gtk::CheckButton AutotrackButton;
	Gtk::Label parentLabel;
	ParentChooser parentChooser;

	std::string name;
	bool autotrack;
	int taskID;
	int numberOfWorkspaces;
	int numColumns;
	int numRows;
	std::vector<int> workspaces;
	int parentID;

	boost::shared_ptr<IAutotrackAccessor> autoTrackAccessor;
	boost::shared_ptr<ITaskAccessor> taskAccessor;
	Workspace workspace;
};
}
}
#endif /*EDITTASKDIALOG_H_*/