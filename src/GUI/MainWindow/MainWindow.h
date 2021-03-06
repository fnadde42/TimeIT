/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * TimeIT
 * Copyright (C) Kent Asplund 2008 <hoglet@solit.se>
 *
 * TimeIT is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * TimeIT is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _MAIN_WINDOW_HPP_
#define _MAIN_WINDOW_HPP_

#include <gtkmm.h>
#include <IWidget.h>
#include <IMainWindow.h>
#include "TaskList.h"
#include "ExtendedTask.h"
#include "SummaryViews.h"
#include "TimeItAboutDialog.h"
#include "Details.h"
#include "Menu.h"
#include "Toolbar.h"
#include "Calendar.h"


namespace GUI
{

class MainWindow: public Gtk::Window, public IActionObserver, public IWidget, public IMainWindow, public DB::ISettingsAccessorObserver
{
public:
	virtual ~MainWindow();
	MainWindow(std::shared_ptr<DB::IDatabase>& database);


	// IWidget interface
	virtual void show() { Gtk::Window::show(); }
	virtual void hide() { Gtk::Window::hide(); }
	virtual bool is_visible() { return Gtk::Window::is_visible(); } ;
	virtual void move(int x, int y) { Gtk::Window::move(x,y); };
	virtual void get_position(int& Window_x, int& Window_y) { Gtk::Window::get_position(Window_x, Window_y); };

	virtual void attach(SummaryObserver* observer);
	virtual void detach(SummaryObserver* observer);
	virtual void attach(IActionObserver*);
	virtual void detach(IActionObserver*);


	virtual ICalendar& getCalendar();

	virtual void on_show();
private:
	//Action observer
	virtual void on_action_task_selection_changed(int selectedTaskID);
	virtual void on_action_remove_task();
	virtual void on_action_start_task() {};
	virtual void on_action_stop_task() {};
	virtual void on_action_edit_task() {};
	virtual void on_action_add_task() {};
	virtual void on_action_add_time() {};
	virtual void on_action_about() {};
	virtual void on_action_help() {};
	virtual void on_action_quit() {};
	virtual void on_action_preferences() {};

	virtual void on_settingsChanged(const std::string& name);


//	virtual void on_selection_changed(int64_t id, time_t startTime, time_t stopTime) {};
//	virtual void on_showDetailsClicked(ISummary* summary, int64_t taskId, time_t startTime, time_t stopTime);
	//
	void createLayout();
	void relateWidgets();
	void setCalendar();
	void connectSignals();

	void defaultLayout();
	void classicLayout();

	void removeChildren(Container& container);
	void emptyContainers();
	void doLayout();

	TaskList       taskList;
	DaySummary    daySummary;
	WeekSummary    weekSummary;
	MonthSummary   monthSummary;
	YearSummary    yearSummary;
	Calendar       calendar;
	Gtk::Notebook  summaryTabs;

	Menu menubar;
	Toolbar toolbar;

	Gtk::HBox  hbox1;
	Gtk::ScrolledWindow  TaskListContainer;
	Gtk::ScrolledWindow  DaySummaryContainer;
	Gtk::Label  labelDay;
	Gtk::ScrolledWindow  WeekSummaryContainer;
	Gtk::Label  labelWeek;
	Gtk::ScrolledWindow  MonthSummaryContainer;
	Gtk::Label  labelMonth;
	Gtk::ScrolledWindow  YearSummaryContainer;
	Gtk::Label  labelYear;

	Gtk::VBox  secondaryVBox; //on right side
	Gtk::HPaned  hPaned;
	Gtk::Statusbar statusbar;
	Gtk::VBox  mainVBox;
	Gtk::HBox  mainHBox;

	std::shared_ptr<DB::IExtendedTaskAccessor> taskAccessor;
	std::shared_ptr<DB::ISettingsAccessor> settingsAccessor;
	std::vector<Summary*> summaries;
};
}
#endif // _MAIN_WINDOW_HPP_
