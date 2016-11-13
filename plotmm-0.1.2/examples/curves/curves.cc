/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * PlotMM Widget Library
 * Copyright (C) 2004   Andy Thaller
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the LGPL
 *****************************************************************************/

#include <plotmm/plot.h>
#include <plotmm/scalediv.h>
#include <plotmm/curve.h>
#include <plotmm/errorcurve.h>
#include <plotmm/symbol.h>
#include <plotmm/paint.h>
#include <plotmm/rectangle.h>

#include <gtkmm/checkbutton.h>
#include <gtkmm/button.h>
#include <gtkmm/box.h>
#include <gtkmm/statusbar.h>
#include <gtkmm/label.h>

#include <gtkmm/window.h>
#include <gtkmm/main.h>

#include <iostream>

class PlotTest : public Gtk::Window
{
public:
  PlotTest();
  virtual ~PlotTest();
 
protected:
  bool button_[3];
  int mx_,my_;
  PlotMM::Rectangle zoomRect_;
  // Child widgets
  Gtk::VBox m_box0;
  Gtk::Statusbar m_sb;

  Glib::RefPtr<PlotMM::ErrorCurve> myCurve0;
  Glib::RefPtr<PlotMM::Curve> myCurve1;
  Glib::RefPtr<PlotMM::Curve> myCurve2;
  Glib::RefPtr<PlotMM::Curve> myCurve3;
  Glib::RefPtr<PlotMM::Curve> myCurve4;

  PlotMM::Plot m_plot;
  int loop;
  int cs;
};

PlotTest::PlotTest() :
  mx_(-1000),my_(-1000),
  m_box0(/*homogeneous*/false, /*spacing*/5), 
  m_sb(), 
  m_plot(),
  loop(0)
{
  // box0
  m_box0.pack_start(m_plot, Gtk::PACK_EXPAND_WIDGET, 5);
  m_plot.set_size_request(500, 300);

  set_border_width(0);
  add(m_box0);
  show_all();

  m_plot.scale(PlotMM::AXIS_LEFT)->set_enabled(false);
  m_plot.scale(PlotMM::AXIS_RIGHT)->set_enabled(false);
  m_plot.scale(PlotMM::AXIS_BOTTOM)->set_enabled(false);
  m_plot.scale(PlotMM::AXIS_TOP)->set_enabled(false);
  
  m_plot.scale(PlotMM::AXIS_BOTTOM)->set_autoscale(true);
  m_plot.scale(PlotMM::AXIS_LEFT)->set_autoscale(true);

  /* set a plot title and some axis labels */
  m_plot.title()->set_text("curve styles");
  m_plot.title()->set_enabled(true);

  /* create some named curves with different colors and symbols */
  myCurve0= Glib::RefPtr<PlotMM::ErrorCurve>(new PlotMM::ErrorCurve("c1"));
  myCurve1= Glib::RefPtr<PlotMM::Curve>(new PlotMM::Curve("c2"));
  myCurve2= Glib::RefPtr<PlotMM::Curve>(new PlotMM::Curve("c3"));
  myCurve3= Glib::RefPtr<PlotMM::Curve>(new PlotMM::Curve("c4"));
  myCurve4= Glib::RefPtr<PlotMM::Curve>(new PlotMM::Curve("c5"));
  myCurve1->paint()->set_pen_color(Gdk::Color("blue"));
  m_plot.add_curve(myCurve1);
  m_plot.add_curve(myCurve2);
  m_plot.add_curve(myCurve3,PlotMM::AXIS_BOTTOM,PlotMM::AXIS_RIGHT);
  m_plot.add_curve(myCurve4,PlotMM::AXIS_TOP);
  m_plot.add_curve(myCurve0);
  myCurve2->paint()->set_pen_color(Gdk::Color("darkblue"));
  myCurve3->paint()->set_pen_color(Gdk::Color("darkgreen"));
  myCurve4->paint()->set_pen_color(Gdk::Color("darkred"));
  myCurve3->symbol()->set_style(PlotMM::SYMBOL_DIAMOND);
  myCurve3->symbol()->set_size(10);
  myCurve3->symbol()->paint()->set_pen_color(Gdk::Color("green"));
  myCurve3->symbol()->paint()->set_brush_color(Gdk::Color("red"));

  /* some special settings for our error curve */
  myCurve0->symbol()->paint()->set_pen_color(Gdk::Color("red"));
  myCurve0->error_paint()->set_pen_color(Gdk::Color("orange"));
  myCurve0->symbol()->set_style(PlotMM::SYMBOL_ELLIPSE);
  myCurve0->symbol()->set_size(10);
  myCurve0->set_curve_style(PlotMM::CURVE_NONE);

  /* of cource we also need data for the curves to show */
  double x1[] = {0,1,2}; double x2[] = {4,5,6};
  double y1[] = {0,1,0}; double y2[] = {2,3,2}; double y3[] = {4,5,4};
  double X1[] = {0.3,0.2,0.1};
  double Y1[] = {0.1,0.2,0.3};

  myCurve0->set_data(x1,y1,X1,Y1,3);
  myCurve1->set_data(x2,y1,3);
  myCurve2->set_data(x1,y2,3);
  myCurve3->set_data(x2,y2,3);
  myCurve4->set_data(x1,y3,3);
}


PlotTest::~PlotTest()
{
}


int main(int argc, char** argv)
{
  Gtk::Main main_instance (argc,argv);
  PlotTest plot;
  Gtk::Main::run(plot);
  return 0;
}

