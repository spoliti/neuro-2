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
  bool timer_callback()
  {
    if (!m_chk_run.get_active()) return 1;

    loop++;
    double r= 400/10000.;
    double x1[10000],x2[10000],y1[10000],y2[10000];
    double phase= loop*.1;
    double x0= 500;
    double y0= 500;
    double ex= 200*sin(phase);;
    double ey= 200*cos(phase);;
    for (int i= 0; i<10000; i++) {
      x1[i]= x0+r*i*sin(phase+r*i*.02); 
      x2[i]= x0-r*i*sin(phase+r*i*.02); 
      y1[i]= y0+r*i*cos(phase+r*i*.07);
      y2[i]= y0-r*i*cos(phase+r*i*.07);
    }
    

    double x3[10], y3[10];
    for (int j=0; j<10; j++) {
      x3[j]= x0+(j-5)*x0/10;
      y3[j]= y0 + y0/3*sin(3.14*j/9+loop*.01);
    }
    
    Glib::Timer timer;
    timer.start();
    myCurve1->set_data(x1,y1,10000);
    myCurve2->set_data(x1,y2,10000);
    myCurve3->set_data(x3,y3,10);
    myCurve3->set_baseline(y0);
    myCurve4->set_data(y3,x3,10);
    myCurve4->set_baseline(y0);
    cs= (loop/50) % PlotMM::CurveStyleCnt;
    myCurve3->set_curve_style(PlotMM::CurveStyleID(cs+1));
    myCurve4->set_curve_style(PlotMM::CurveStyleID(cs+1),
			    PlotMM::CURVE_X_FY);
    myCurve0->set_data(&x0,&y0,&ex,&ey,1);

    m_plot.replot();
    timer.stop();
   
    fps_.stop();
    double time= fps_.elapsed();
    fps_.start();
    char tmp[100];
    sprintf(tmp,"%.1f fps",1/time);
    l_fps.set_text(tmp);
    print_coords(mx_,my_);
    return 1;
  }
  
  void on_scale_toggled(PlotMM::PlotAxisID id,const Gtk::CheckButton *chk) 
  {
    m_plot.scale(id)->set_enabled(chk->get_active());
    m_plot.label(id)->set_enabled(chk->get_active());
  }

  void on_plot_mouse_press(int x,int y, GdkEventButton *ev)
  {
    if (ev->button>0 && ev->button<4) button_[ev->button-1]= true;
    print_coords(mx_=x,my_=y);

    
    if ((ev->button==1)) {  // zoom
      m_plot.scale(PlotMM::AXIS_BOTTOM)->set_autoscale(false);
      m_plot.scale(PlotMM::AXIS_LEFT)->set_autoscale(false);
      zoomRect_.set_rect(x,y,0,0);
      m_plot.set_selection(zoomRect_);
      m_plot.enable_selection();
    } else if ((ev->button==3)) {  // unzoom
      m_plot.scale(PlotMM::AXIS_BOTTOM)->set_autoscale(true);
      m_plot.scale(PlotMM::AXIS_LEFT)->set_autoscale(true);
      m_plot.replot();
   }
  }

  void on_plot_mouse_release(int x,int y, GdkEventButton *ev)
  {
    if (ev->button>0 && ev->button<4) button_[ev->button-1]= false;
    print_coords(mx_=x,my_=y);

    if ((ev->button==1)) {
      double x0,y0,x1,y1;
      int ix0,iy0,ix1,iy1;
      zoomRect_= m_plot.get_selection();
      ix0= zoomRect_.get_x_min(); 
      ix1= zoomRect_.get_x_max();
      iy0= zoomRect_.get_y_min(); 
      iy1= zoomRect_.get_y_max();
      x0= m_plot.scale(PlotMM::AXIS_BOTTOM)->scale_map().inv_transform(ix0);
      x1= m_plot.scale(PlotMM::AXIS_BOTTOM)->scale_map().inv_transform(ix1);
      y0= m_plot.scale(PlotMM::AXIS_LEFT)->scale_map().inv_transform(iy1);
      y1= m_plot.scale(PlotMM::AXIS_LEFT)->scale_map().inv_transform(iy0);
      m_plot.disable_selection();
      if (zoomRect_.get_width()==0 && zoomRect_.get_height()==0)
	return;
      m_plot.scale(PlotMM::AXIS_BOTTOM)->set_range(x0,x1);
      m_plot.scale(PlotMM::AXIS_LEFT)->set_range(y0,y1);
      m_plot.replot();
    }
  }

  void on_plot_mouse_move(int x,int y, GdkEventMotion *ev)
  {
    print_coords(mx_=x,my_=y);
    zoomRect_.set_destination(x,y);
    m_plot.set_selection(zoomRect_);
  }

  void print_coords(int x, int y)
  {
    char tmp[1000];
    sprintf(tmp,"(%d,%d): b:%8g; t:%8g; l:%8g; r:%8g; %c%c%c",x,y,
	    m_plot.scale(PlotMM::AXIS_BOTTOM)->scale_map().inv_transform(x),
	    m_plot.scale(PlotMM::AXIS_TOP)->scale_map().inv_transform(x),
	    m_plot.scale(PlotMM::AXIS_LEFT)->scale_map().inv_transform(y),
	    m_plot.scale(PlotMM::AXIS_RIGHT)->scale_map().inv_transform(y),
	    button_[0]?'*':'O',button_[1]?'*':'O',button_[2]?'*':'O');
    m_sb.pop();
    if (x>-1000&&y>-1000)
      m_sb.push(tmp);
  }
 
protected:
  bool button_[3];
  int mx_,my_;
  PlotMM::Rectangle zoomRect_;
  // Child widgets
  Gtk::Label l_fps;
  Gtk::CheckButton m_chk_l;
  Gtk::CheckButton m_chk_r;
  Gtk::CheckButton m_chk_t;
  Gtk::CheckButton m_chk_b;
  Gtk::CheckButton m_chk_run;
  Gtk::VBox m_box0;
  Gtk::HBox m_box1;
  Gtk::VBox m_box2;
  Gtk::VBox m_box3; //empty box

  Gtk::Button m_button1, m_button2;
  Gtk::Statusbar m_sb;

  Glib::RefPtr<PlotMM::ErrorCurve> myCurve0;
  Glib::RefPtr<PlotMM::Curve> myCurve1;
  Glib::RefPtr<PlotMM::Curve> myCurve2;
  Glib::RefPtr<PlotMM::Curve> myCurve3;
  Glib::RefPtr<PlotMM::Curve> myCurve4;

  PlotMM::Plot m_plot;
  Glib::Timer fps_;
  int loop;
  int cs;
};

PlotTest::PlotTest() :
  mx_(-1000),my_(-1000),
  l_fps("",Gtk::ALIGN_RIGHT),
  m_chk_l("Left"),
  m_chk_r("Right"),
  m_chk_t("Top"),
  m_chk_b("Bottom"),
  m_chk_run("Animate"),
  m_box0(/*homogeneous*/false, /*spacing*/5), 
  m_box1(false, 5), m_box2(false, 5), m_box3(false, 5),
  m_button1("Dialog"), m_button2("Quit"), 
  m_sb(), 
  m_plot(),
  loop(0)
{
  fps_.start();
  button_[0]= button_[1]= button_[2]= false;
  // box2
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION >= 4)
  m_button2.signal_clicked().connect(sigc::mem_fun(*this, &Gtk::Widget::hide));
#else
  m_button2.signal_clicked().connect(SigC::slot(*this, &Gtk::Widget::hide));
#endif
  m_box3.pack_start(m_chk_t, Gtk::PACK_SHRINK,5);
  m_box3.pack_start(m_chk_l, Gtk::PACK_SHRINK,5);
  m_box3.pack_start(m_chk_r, Gtk::PACK_SHRINK,5);
  m_box3.pack_start(m_chk_b, Gtk::PACK_SHRINK,5);
  m_box3.pack_start(l_fps, Gtk::PACK_SHRINK,5);
  m_box2.pack_start(m_box3, Gtk::PACK_EXPAND_WIDGET, /*padding*/5);
  //m_box2.pack_start(m_button1, Gtk::PACK_SHRINK, 5);
  m_box2.pack_start(m_chk_run, Gtk::PACK_SHRINK, 5);
  m_box2.pack_start(m_button2, Gtk::PACK_SHRINK, 5);

  // box1
  m_plot.set_size_request(500, 300);
  m_box1.pack_start(m_plot, Gtk::PACK_EXPAND_WIDGET, 5);
  m_box1.pack_start(m_box2, Gtk::PACK_SHRINK, 5);
    
  // box0
  m_box0.pack_start(m_box1, Gtk::PACK_EXPAND_WIDGET, 5);
  m_box0.pack_start(m_sb, Gtk::PACK_SHRINK, 5);
  
  set_border_width(0);
  add(m_box0);
  show_all();

#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION >= 4)
  m_plot.signal_plot_mouse_press().
    connect(sigc::mem_fun(*this,&PlotTest::on_plot_mouse_press));
  m_plot.signal_plot_mouse_release().
    connect(sigc::mem_fun(*this,&PlotTest::on_plot_mouse_release));
  m_plot.signal_plot_mouse_move().
    connect(sigc::mem_fun(*this,&PlotTest::on_plot_mouse_move));
  m_button2.signal_clicked().connect(sigc::mem_fun(*this, &Gtk::Widget::hide));
#else
  m_plot.signal_plot_mouse_press().
    connect(SigC::slot(*this,&PlotTest::on_plot_mouse_press));
  m_plot.signal_plot_mouse_release().
    connect(SigC::slot(*this,&PlotTest::on_plot_mouse_release));
  m_plot.signal_plot_mouse_move().
    connect(SigC::slot(*this,&PlotTest::on_plot_mouse_move));
  m_button2.signal_clicked().connect(SigC::slot(*this, &Gtk::Widget::hide));
#endif

#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION >= 4)
#define CHECKBOX_SCALE_HELPER(AXIS,CHECKBOX) \
  m_plot.scale(AXIS)->signal_enabled.connect(sigc::mem_fun(CHECKBOX,&Gtk::CheckButton::set_active));\
  CHECKBOX.signal_toggled().connect(sigc::bind(sigc::mem_fun(*this,&PlotTest::on_scale_toggled),AXIS,&CHECKBOX));\
  m_plot.scale(AXIS)->set_enabled(true)
#else
#define CHECKBOX_SCALE_HELPER(AXIS,CHECKBOX) \
  m_plot.scale(AXIS)->signal_enabled.connect(SigC::slot(CHECKBOX,&Gtk::CheckButton::set_active));\
  CHECKBOX.signal_toggled().connect(SigC::bind(SigC::slot(*this,&PlotTest::on_scale_toggled),AXIS,&CHECKBOX));\
  m_plot.scale(AXIS)->set_enabled(true)
#endif

  CHECKBOX_SCALE_HELPER(PlotMM::AXIS_TOP,m_chk_t);
  CHECKBOX_SCALE_HELPER(PlotMM::AXIS_BOTTOM,m_chk_b);
  CHECKBOX_SCALE_HELPER(PlotMM::AXIS_LEFT,m_chk_l);
  CHECKBOX_SCALE_HELPER(PlotMM::AXIS_RIGHT,m_chk_r);
#undef CHECKBOX_SCALE_HELPER

  /* set some axes to linear and others to logarithmic scale */
  m_plot.scale(PlotMM::AXIS_BOTTOM)->set_range(-10,1000,false);
  m_plot.scale(PlotMM::AXIS_TOP)->set_range(10,1000,true);
  m_plot.scale(PlotMM::AXIS_LEFT)->set_range(-10,1000,false);
  m_plot.scale(PlotMM::AXIS_RIGHT)->set_range(10,1000,true);
  /* allow for autoscaling on all axes */
  m_plot.scale(PlotMM::AXIS_TOP)->set_autoscale(true);
  m_plot.scale(PlotMM::AXIS_RIGHT)->set_autoscale(true);
  m_plot.scale(PlotMM::AXIS_BOTTOM)->set_autoscale(true);
  m_plot.scale(PlotMM::AXIS_LEFT)->set_autoscale(true);
  /* set a plot title and some axis labels */
  m_plot.title()->set_text("A simple plot");
  m_plot.title()->set_enabled(true);
  m_plot.label(PlotMM::AXIS_TOP)->set_text("top axis");
  m_plot.label(PlotMM::AXIS_RIGHT)->set_text("right axis");
  m_plot.label(PlotMM::AXIS_BOTTOM)->set_text("bottom axis");
  m_plot.label(PlotMM::AXIS_LEFT)->set_text("left axis");

  /* create some named curves with different colors and symbols */
  myCurve0= Glib::RefPtr<PlotMM::ErrorCurve>(new PlotMM::ErrorCurve("huhu 0"));
  myCurve1= Glib::RefPtr<PlotMM::Curve>(new PlotMM::Curve("huhu 1"));
  myCurve2= Glib::RefPtr<PlotMM::Curve>(new PlotMM::Curve("huhu 2"));
  myCurve3= Glib::RefPtr<PlotMM::Curve>(new PlotMM::Curve("huhu 3"));
  myCurve4= Glib::RefPtr<PlotMM::Curve>(new PlotMM::Curve("huhu 4"));
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

  m_chk_run.set_active(true);
#if (GTKMM_MAJOR_VERSION == 2 && GTKMM_MINOR_VERSION >= 4)
  Glib::signal_timeout().connect(sigc::mem_fun(*this, &PlotTest::timer_callback),
				 10,Glib::PRIORITY_DEFAULT_IDLE);
#else
  Glib::signal_timeout().connect(SigC::slot(*this, &PlotTest::timer_callback),
				 10,Glib::PRIORITY_DEFAULT_IDLE);
#endif
}


PlotTest::~PlotTest()
{
}






int test_scalediv(int argc, char** argv)
{
  int i,k;
  PlotMM::ScaleDiv sd;

  sd.rebuild(0.0064, 1012, 10, 10, true, 0.0);

  k=0;
  for (i=0;i<sd.maj_count();i++) {
    while(k < sd.min_count()) {
      if (sd.min_mark(k) < sd.maj_mark(i)) {
        std::cout << " - " << sd.min_mark(k) << "\n";
	k++;
      } else break;
    }
    std::cout << "-- " << sd.maj_mark(i) << "\n";
  }
  while(k < sd.min_count()) {
    std::cout << " - " << sd.min_mark(k) << "\n";
    k++;
  }
  return 0;
}

int test_plot(int argc, char** argv) 
{
    Gtk::Main main_instance (argc,argv);
    PlotTest plot;
    Gtk::Main::run(plot);
    return 0;
}



int main(int argc, char** argv)
{
  // test_scalediv(argc,argv);
  test_plot(argc,argv);

  return 0;
}

