#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

float bijelo[] = {1.0f, 1.0f, 1.0f, 1.0f};
float crno[] = {0.0f, 0.0f, 0.0f, 1.0f};
float smedje[] = {238.0f / 255.0f, 154.0f / 255.0f, 73.0f / 255.0f};
float zuto[] = {250.0f / 255.0f, 247.0f / 255.0f, 65.0f / 255.0f};
float sivo[] = {135.0f / 255.0f, 135.0f / 255.0f, 135.0f / 255.0f};
float crveno[] = {252.0f / 255.0f, 5.0f / 255.0f, 38.0f / 255.0f};

double kut = 0.0;
double betta = 0.0;
double gama = 0.0;
double delta = 0.0;
double epsilon = 0.0;
//int verzija = 0, nn = 16;

void normiraj(double *v) {
  double d = sqrt(v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
  v[0] /= d; v[1] /= d; v[2] /= d;
} // normiraj

void vprodukt(double *v, double a0, double a1, double a2,
              double b0, double b1, double b2) {
  v[0] = a1 * b2 - a2 * b1;
  v[1] = a2 * b0 - a0 * b2;
  v[2] = a0 * b1 - a1 * b0;
} // vprodukt

void kocka(double a) {
  glBegin(GL_QUADS);
    glNormal3d(0.0, 0.0, -1.0);
    glVertex3d(0.0, 0.0, 0.0); glVertex3d(0.0, a, 0.0);
    glVertex3d(a, a, 0.0); glVertex3d(a, 0.0, 0.0);

    glNormal3d(0.0, 0.0, 1.0);
    glVertex3d(0.0, 0.0, a); glVertex3d(a, 0.0, a);
    glVertex3d(a, a, a); glVertex3d(0.0, a, a);
  glEnd();

  glBegin(GL_QUAD_STRIP);
    glNormal3d(0.0, -1.0, 0.0);
    glVertex3d(0.0, 0.0, a); glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(a, 0.0, a); glVertex3d(a, 0.0, 0.0);

    glNormal3d(1.0, 0.0, 0.0);    
    glVertex3d(a, a, a); glVertex3d(a, a, 0.0);

    glNormal3d(0.0, 1.0, 0.0);
    glVertex3d(0.0, a, a); glVertex3d(0.0, a, 0.0);

    glNormal3d(-1.0, 0.0, 0.0);
    glVertex3d(0.0, 0.0, a); glVertex3d(0.0, 0.0, 0.0);
  glEnd();
} // kocka


void stozac(double r, double h, int n) {
  double t;
  int i;

  // baza stošca
  glBegin(GL_TRIANGLES);
    t = 0.0;
    for(i = 0; i <= n; i++) {
      if(i%2==0){
         glColor3d(0.0, 1.0, 0.0);
      }else{
        glColor3d(0.0, 0.0, 1.0);
      }
      glNormal3d(0.0, 0.0, -1.0);
      glVertex3d(0.0, 0.0, 0.0);
      glNormal3d(cos(t), sin(t), 0.0);
      glVertex3d(r * cos(t), r * sin(t), 0.0);
      glNormal3d(cos(t+2.0 * M_PI / n), sin(t+2.0 * M_PI / n), 0.0);
      glVertex3d(r * cos(t+2.0 * M_PI / n), r * sin(t+2.0 * M_PI / n), 0.0);
      t += 2.0 * M_PI / n;
    }
  glEnd();

  // plašt stošca
  glBegin(GL_TRIANGLES); 
    t = 2.0 * M_PI;
    for(i = 0; i <= n; i++) {
      if(i%2==0){
         glColor3d(0.0, 1.0, 0.0);
      }else{
        glColor3d(0.0, 0.0, 1.0);
      }
      glNormal3d(0.0, 0.0, 1.0);// normala u vrhu stošca u smjeru +z
      glVertex3d(0.0, 0.0, h);
      glNormal3d(cos(t), sin(t), 0.0);
      glVertex3d(r * cos(t), r * sin(t), 0.0);
      glNormal3d(cos(t+2.0 * M_PI / n), sin(t+2.0 * M_PI / n), 0.0);
      glVertex3d(r * cos(t+2.0 * M_PI / n), r * sin(t+2.0 * M_PI / n), 0.0);
      t -= 2.0 * M_PI / n;
    }
  glEnd();
} // stozac


void stozac2(double r, double h, int n) {
  double t;
  int i;

/*  // baza stošca
  glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0.0, 0.0, -1.0); // normala je u smjeru -z za sve trokute
    glVertex3d(0.0, 0.0, 0.0);
    t = 0.0;
    for(i = 0; i <= n; i++) {
      if(i%2==0){
         glColor3d(0.0, 1.0, 0.0);
      }else{
        glColor3d(0.0, 0.0, 1.0);
      }
      glVertex3d(r * cos(t), r * sin(t), 0.0);
      t += 2.0 * M_PI / n;
    }
  glEnd();*/

  // plašt stošca
  glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0.0, 0.0, 1.0); // normala u vrhu stošca u smjeru +z
    glVertex3d(0.0, 0.0, h);
    t = 2.0 * M_PI;
    for(i = 0; i <= n; i++) {
      if(i%2==0){
         glColor3d(0.0, 1.0, 0.0);
      }else{
        glColor3d(0.0, 0.0, 1.0);
      }
      glNormal3d(cos(t), sin(t), 0.0); // normale u xy ravnini - od središta
      glVertex3d(r * cos(t), r * sin(t), 0.0);
      t -= 2.0 * M_PI / n;
    }
  glEnd();
} // stozac2

void valjak(double r, double h, int n) {
  double t;
  int i;

  // baza valjka dolje
  glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0.0, 0.0, -1.0); // normala je u smjeru -z za sve trokute
    glVertex3d(0.0, 0.0, 0.0);
    t = 0.0;
    for(i = 0; i <= n; i++) {
      if(i%2==0){
         glColor3d(0.0, 1.0, 0.0);
      }else{
        glColor3d(0.0, 0.0, 1.0);
      }
      glVertex3d(r * cos(t), r * sin(t), 0.0);
      t += 2.0 * M_PI / n;
    }
  glEnd();

  // baza valjka gore
  glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0.0, 0.0, 1.0); // normala je u smjeru -z za sve trokute
    glVertex3d(0.0, 0.0, h);
    t = 0.0;
    for(i = 0; i <= n; i++) {
      if(i%2==0){
         glColor3d(0.0, 1.0, 0.0);
      }else{
        glColor3d(0.0, 0.0, 1.0);
      }
      glVertex3d(r * cos(t), r * sin(t), h);
      t += 2.0 * M_PI / n;
    }
  glEnd();

  // plašt valjka
  glBegin(GL_QUAD_STRIP);    
    t = 2.0 * M_PI;
    for(i = 0; i <= n; i++) {
      if(i%2==0){
         glColor3d(0.0, 1.0, 0.0);
      }else{
        glColor3d(0.0, 0.0, 1.0);
      }
      glNormal3d(cos(t), sin(t), h/r);
      glVertex3d(r * cos(t), r * sin(t), h);
      glNormal3d(cos(t), sin(t), 0.0);
      glVertex3d(r * cos(t), r * sin(t), 0.0);
      glNormal3d(cos(t-2.0 * M_PI / n), sin(t-2.0 * M_PI / n), h/r);
      glVertex3d(r * cos(t-2.0 * M_PI / n), r * sin(t-2.0 * M_PI / n), h);
      glNormal3d(cos(t-2.0 * M_PI / n), sin(t-2.0 * M_PI / n), 0.0);
      glVertex3d(r * cos(t-2.0 * M_PI / n), r * sin(t-2.0 * M_PI / n), 0.0);
      t -= 2.0 * M_PI / n;
    }
  glEnd();
} // valjak


void kugla(double r, int n, int m){
  double fi,alfa;
  int i=1;
  int j=1;
  
  glBegin(GL_QUAD_STRIP);
  for(fi=0.0; fi<2.0*M_PI;fi=fi+(2.0*M_PI/n)){
      for(alfa=0.0; alfa<2.0*M_PI;alfa=alfa+(2.0*M_PI/m)){
	if((i+j)%2==0){
	  glColor3d(0.0, 1.0, 0.0);
        }else{
          glColor3d(0.0, 0.0, 1.0);
        }
        glNormal3d(sin(fi)*cos(alfa), sin(fi)*sin(alfa), cos(fi));
    	glVertex3d(r*sin(fi)*cos(alfa), r*sin(fi)*sin(alfa), r*cos(fi));
	glNormal3d(sin(fi+2.0*M_PI/n)*cos(alfa), sin(fi+2.0*M_PI/n)*sin(alfa), cos(fi+2.0*M_PI/n));
	glVertex3d(r*sin(fi+2.0*M_PI/n)*cos(alfa), r*sin(fi+2.0*M_PI/n)*sin(alfa), r*cos(fi+2.0*M_PI/n));
	glNormal3d(sin(fi)*cos(alfa+2.0*M_PI/m), sin(fi)*sin(alfa+2.0*M_PI/m), cos(fi));
	glVertex3d(r*sin(fi)*cos(alfa+2.0*M_PI/m), r*sin(fi)*sin(alfa+2.0*M_PI/m), r*cos(fi));
	glNormal3d(sin(fi+2.0*M_PI/n)*cos(alfa+2.0*M_PI/m), sin(fi+2.0*M_PI/n)*sin(alfa+2.0*M_PI/m), cos(fi+2.0*M_PI/n));
	glVertex3d(r*sin(fi+2.0*M_PI/n)*cos(alfa+2.0*M_PI/m), r*sin(fi+2.0*M_PI/n)*sin(alfa+2.0*M_PI/m), r*cos(fi+2.0*M_PI/n));
	j++;
     }
     i++;    
  }
  glEnd();
} //kugla


void polukugla(double r, int n, int m){
  double fi,alfa;
  int i=1;
  int j=1;

  glBegin(GL_QUAD_STRIP);
  for(fi=0.0; fi<M_PI;fi=fi+(2.0*M_PI/n)){
      for(alfa=0.0; alfa<M_PI;alfa=alfa+(2.0*M_PI/m)){
	if((i+j)%2==0){
	  glColor3d(0.0, 1.0, 0.0);
        }else{
          glColor3d(0.0, 0.0, 1.0);
        }
        glNormal3d(sin(fi)*cos(alfa), sin(fi)*sin(alfa), cos(fi));
    	glVertex3d(r*sin(fi)*cos(alfa), r*sin(fi)*sin(alfa), r*cos(fi));
	glNormal3d(sin(fi+2.0*M_PI/n)*cos(alfa), sin(fi+2.0*M_PI/n)*sin(alfa), cos(fi+2.0*M_PI/n));
	glVertex3d(r*sin(fi+2.0*M_PI/n)*cos(alfa), r*sin(fi+2.0*M_PI/n)*sin(alfa), r*cos(fi+2.0*M_PI/n));
	glNormal3d(sin(fi)*cos(alfa+2.0*M_PI/m), sin(fi)*sin(alfa+2.0*M_PI/m), cos(fi));
	glVertex3d(r*sin(fi)*cos(alfa+2.0*M_PI/m), r*sin(fi)*sin(alfa+2.0*M_PI/m), r*cos(fi));
	glNormal3d(sin(fi+2.0*M_PI/n)*cos(alfa+2.0*M_PI/m), sin(fi+2.0*M_PI/n)*sin(alfa+2.0*M_PI/m), cos(fi+2.0*M_PI/n));
	glVertex3d(r*sin(fi+2.0*M_PI/n)*cos(alfa+2.0*M_PI/m), r*sin(fi+2.0*M_PI/n)*sin(alfa+2.0*M_PI/m), r*cos(fi+2.0*M_PI/n));
	j++;
     }
     i++;    
  }
  glEnd();
} //polukugla


void elipsoida(double a,double b,double c, int n, int m){
  double fi,alfa;
  int i=1;
  int j=1;
  
  glBegin(GL_QUAD_STRIP);
  for(fi=0.0; fi<2.0*M_PI;fi=fi+(2.0*M_PI/n)){
      for(alfa=0.0; alfa<2.0*M_PI;alfa=alfa+(2.0*M_PI/m)){
	if((i+j)%2==0){
	  glColor3d(0.0, 1.0, 0.0);
        }else{
          glColor3d(0.0, 0.0, 1.0);
        }
        glNormal3d(sin(fi)*cos(alfa), sin(fi)*sin(alfa), cos(fi));
    	glVertex3d(a*sin(fi)*cos(alfa), b*sin(fi)*sin(alfa), c*cos(fi));
	glNormal3d(sin(fi+2.0*M_PI/n)*cos(alfa), sin(fi+2.0*M_PI/n)*sin(alfa), cos(fi+2.0*M_PI/n));
	glVertex3d(a*sin(fi+2.0*M_PI/n)*cos(alfa), b*sin(fi+2.0*M_PI/n)*sin(alfa), c*cos(fi+2.0*M_PI/n));
	glNormal3d(sin(fi)*cos(alfa+2.0*M_PI/m), sin(fi)*sin(alfa+2.0*M_PI/m), cos(fi));
	glVertex3d(a*sin(fi)*cos(alfa+2.0*M_PI/m), b*sin(fi)*sin(alfa+2.0*M_PI/m), c*cos(fi));
	glNormal3d(sin(fi+2.0*M_PI/n)*cos(alfa+2.0*M_PI/m), sin(fi+2.0*M_PI/n)*sin(alfa+2.0*M_PI/m), cos(fi+2.0*M_PI/n));
	glVertex3d(a*sin(fi+2.0*M_PI/n)*cos(alfa+2.0*M_PI/m), b*sin(fi+2.0*M_PI/n)*sin(alfa+2.0*M_PI/m), c*cos(fi+2.0*M_PI/n));
	j++;
     }
     i++;    
  }
  glEnd();
} //elipsoida

void kvadar(double a, double b,double c) {
    glBegin(GL_QUADS);
    glNormal3d(0.0, 0.0, -1.0);
    glVertex3d(0.0, 0.0, 0.0); glVertex3d(0.0, b, 0.0);
    glVertex3d(a, b, 0.0); glVertex3d(a, 0.0, 0.0);

    glNormal3d(0.0, 0.0, 1.0);
    glVertex3d(0.0, 0.0, c); glVertex3d(a, 0.0, c);
    glVertex3d(a, b, c); glVertex3d(0.0, b, c);
  glEnd();

  glBegin(GL_QUAD_STRIP);
    glNormal3d(0.0, -1.0, 0.0);
    glVertex3d(0.0, 0.0, c); glVertex3d(0.0, 0.0, 0.0);
    glVertex3d(a, 0.0, c); glVertex3d(a, 0.0, 0.0);

    glNormal3d(1.0, 0.0, 0.0);    
    glVertex3d(a, b, c); glVertex3d(a, b, 0.0);

    glNormal3d(0.0, 1.0, 0.0);
    glVertex3d(0.0, b, c); glVertex3d(0.0, b, 0.0);

    glNormal3d(-1.0, 0.0, 0.0);
    glVertex3d(0.0, 0.0, b); glVertex3d(0.0, 0.0, 0.0);
  glEnd();
}


void poluvaljak(double r, double h, int n) {
  double t;
  int i;

  // baza valjka dolje
  glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0.0, 0.0, -1.0); // normala je u smjeru -z za sve trokute
    glVertex3d(0.0, 0.0, 0.0);
    t = 0.0;
    for(i = 0; i <= n; i++) {
      if(i%2==0){
         glColor3d(0.0, 1.0, 0.0);
      }else{
        glColor3d(0.0, 0.0, 1.0);
      }
      glVertex3d(r * cos(t), r * sin(t), 0.0);
      t += M_PI / n;
    }
  glEnd();

  // baza valjka gore
  glBegin(GL_TRIANGLE_FAN);
    glNormal3d(0.0, 0.0, 1.0); // normala je u smjeru -z za sve trokute
    glVertex3d(0.0, 0.0, h);
    t = 0.0;
    for(i = 0; i <= n; i++) {
      if(i%2==0){
         glColor3d(0.0, 1.0, 0.0);
      }else{
        glColor3d(0.0, 0.0, 1.0);
      }
      glVertex3d(r * cos(t), r * sin(t), h);
      t += M_PI / n;
    }
  glEnd();

  // plašt valjka
  glBegin(GL_QUAD_STRIP);    
    t = M_PI;
    for(i = 0; i <= n; i++) {
      if(i%2==0){
         glColor3d(0.0, 1.0, 0.0);
      }else{
        glColor3d(0.0, 0.0, 1.0);
      }
      glNormal3d(cos(t), sin(t), h/r);
      glVertex3d(r * cos(t), r * sin(t), h);
      glNormal3d(cos(t), sin(t), 0.0);
      glVertex3d(r * cos(t), r * sin(t), 0.0);
      glNormal3d(cos(t- M_PI / n), sin(t-M_PI / n), h/r);
      glVertex3d(r * cos(t- M_PI / n), r * sin(t- M_PI / n), h);
      glNormal3d(cos(t- M_PI / n), sin(t- M_PI / n), 0.0);
      glVertex3d(r * cos(t- M_PI / n), r * sin(t- M_PI / n), 0.0);
      t -= M_PI / n;
    }
  glEnd();
} // poluvaljak


void prsten(double r,double d, double h, int n) {
  double t;
  int i;

  // baza valjka dolje
//  glBegin(GL_TRIANGLE_FAN);
//    glNormal3d(0.0, 0.0, -1.0); // normala je u smjeru -z za sve trokute
//    glVertex3d(0.0, 0.0, 0.0);
//    t = 0.0;
//    for(i = 0; i <= n; i++) {
//      if(i%2==0){
//         glColor3d(0.0, 1.0, 0.0);
//      }else{
//        glColor3d(0.0, 0.0, 1.0);
//      }
//      glVertex3d(r * cos(t), r * sin(t), 0.0);
//      t += 2.0 * M_PI / n;
//    }
//  glEnd();

  // gornji rub
  glBegin(GL_QUAD_STRIP);    
    t = 2.0 * M_PI;
    for(i = 0; i <= n; i++) {
      if(i%2==0){
         glColor3d(0.0, 1.0, 0.0);
      }else{
        glColor3d(0.0, 0.0, 1.0);
      }
      glNormal3d(cos(t), sin(t), h/r);
      glVertex3d(r * cos(t), r * sin(t), h);
      glNormal3d(cos(t), sin(t), h/(r-d));
      glVertex3d((r-d) * cos(t), (r-d) * sin(t), h);
      glNormal3d(cos(t-2.0 * M_PI / n), sin(t-2.0 * M_PI / n), h/r);
      glVertex3d(r * cos(t-2.0 * M_PI / n), r * sin(t-2.0 * M_PI / n), h);
      glNormal3d(cos(t-2.0 * M_PI / n), sin(t-2.0 * M_PI / n), h/(r-d));
      glVertex3d((r-d) * cos(t-2.0 * M_PI / n), (r-d) * sin(t-2.0 * M_PI / n), h);
      t -= 2.0 * M_PI / n;
    }
  glEnd();

  // donji rub
  glBegin(GL_QUAD_STRIP);    
    t = 2.0 * M_PI;
    for(i = 0; i <= n; i++) {
      if(i%2==0){
         glColor3d(0.0, 1.0, 0.0);
      }else{
        glColor3d(0.0, 0.0, 1.0);
      }
      glNormal3d(cos(t), sin(t), 0.0);
      glVertex3d(r * cos(t), r * sin(t), 0.0);
      glNormal3d(cos(t), sin(t), 0.0);
      glVertex3d((r-d) * cos(t), (r-d) * sin(t), 0.0);
      glNormal3d(cos(t-2.0 * M_PI / n), sin(t-2.0 * M_PI / n), 0.0);
      glVertex3d(r * cos(t-2.0 * M_PI / n), r * sin(t-2.0 * M_PI / n), 0.0);
      glNormal3d(cos(t-2.0 * M_PI / n), sin(t-2.0 * M_PI / n), 0.0);
      glVertex3d((r-d) * cos(t-2.0 * M_PI / n), (r-d) * sin(t-2.0 * M_PI / n), 0.0);
      t -= 2.0 * M_PI / n;
    }
  glEnd();

  // vanjski rub
  glBegin(GL_QUAD_STRIP);    
    t = 2.0 * M_PI;
    for(i = 0; i <= n; i++) {
      if(i%2==0){
         glColor3d(0.0, 1.0, 0.0);
      }else{
        glColor3d(0.0, 0.0, 1.0);
      }
      glNormal3d(cos(t), sin(t), h/r);
      glVertex3d(r * cos(t), r * sin(t), h);
      glNormal3d(cos(t), sin(t), 0.0);
      glVertex3d(r * cos(t), r * sin(t), 0.0);
      glNormal3d(cos(t-2.0 * M_PI / n), sin(t-2.0 * M_PI / n), h/r);
      glVertex3d(r * cos(t-2.0 * M_PI / n), r * sin(t-2.0 * M_PI / n), h);
      glNormal3d(cos(t-2.0 * M_PI / n), sin(t-2.0 * M_PI / n), 0.0);
      glVertex3d(r * cos(t-2.0 * M_PI / n), r * sin(t-2.0 * M_PI / n), 0.0);
      t -= 2.0 * M_PI / n;
    }
  glEnd();

  // unutarnji rub
  glBegin(GL_QUAD_STRIP);    
    t = 2.0 * M_PI;
    for(i = 0; i <= n; i++) {
      if(i%2==0){
         glColor3d(0.0, 1.0, 0.0);
      }else{
        glColor3d(0.0, 0.0, 1.0);
      }
      glNormal3d(cos(t), sin(t), h/(r-d));
      glVertex3d((r-d) * cos(t), (r-d) * sin(t), h);
      glNormal3d(cos(t), sin(t), 0.0);
      glVertex3d((r-d) * cos(t), (r-d) * sin(t), 0.0);
      glNormal3d(cos(t-2.0 * M_PI / n), sin(t-2.0 * M_PI / n), h/(r-d));
      glVertex3d((r-d) * cos(t-2.0 * M_PI / n), (r-d) * sin(t-2.0 * M_PI / n), h);
      glNormal3d(cos(t-2.0 * M_PI / n), sin(t-2.0 * M_PI / n), 0.0);
      glVertex3d((r-d) * cos(t-2.0 * M_PI / n), (r-d) * sin(t-2.0 * M_PI / n), 0.0);
      t -= 2.0 * M_PI / n;
    }
  glEnd();
} // prsten

void vjetrenjaca() {
  glPushMatrix(); 
  glEnable(GL_DEPTH_TEST);
  stozac(3,8,14);  
  
  glTranslated(0,0,5.5); 
  glRotated(kut*2, 0.0, 0.0, 1.0);
  valjak(1,2,14);
  
  glTranslated(0,0,2/2.0);
  glRotated(90, 1.0,0.0, 0.0);
  valjak(0.3,7,14);
  glRotated(120, 0.0,1.0, 0.0);
  valjak(0.3,7,14);
  glRotated(120, 0.0,1.0, 0.0);
  valjak(0.3,7,14);

  glDisable(GL_DEPTH_TEST);
  glPopMatrix();
  glRotated(kut*2, 0.0,0.0, 1.0);

  glPushMatrix(); 
  glRotated(60, 0.0,0.0, 1.0);
  glTranslated(0,7+1/2.0,5.5+2/2.0);
  glRotated(-90, 0.0,0.0, 1.0);
  polukugla(1,20,20);
  glPopMatrix();

  glPushMatrix(); 
  glRotated(180, 0.0,0.0, 1.0);
  glTranslated(0,7+1/2.0,5.5+2/2.0);
  glRotated(-90, 0.0,0.0, 1.0);
  polukugla(1,20,20);
  glPopMatrix();

  glPushMatrix(); 
  glRotated(-60, 0.0,0.0, 1.0);
  glTranslated(0,7+1/2.0,5.5+2/2.0);
  glRotated(-90, 0.0,0.0, 1.0);
  polukugla(1,20,20);
  glPopMatrix();
}

void bager() {
   glPushMatrix();
   kvadar (10,7,2);
   glTranslated(0,0,1);
   glRotated(-90, 1.0,0.0,0.0);
   valjak(1,7,70);
   glTranslated(10,0,0);
   valjak(1,7,70);
   glMaterialfv(GL_FRONT, GL_DIFFUSE, zuto);
   glPopMatrix();
   glTranslated(5,3.5,1); 
   glRotated(betta,0,0,1);
   glTranslated(-5,-3.5,-1); 
   glTranslated(0,0,2);    
   kvadar (10,7,2);
   glTranslated(0,2.5,2);
   glRotated(-90, 1.0,0.0,0.0);
   valjak(0.5,1.5,70);
   glPushMatrix();
   glTranslated(-0.2,0.5,0.0);
   glRotated(-135+gama, 0,0,1);
   kvadar(7,1,1.5);
   glPopMatrix();
   glPushMatrix();
   glRotated(-135+gama, 0,0,1);
   glTranslated(7,0,0);
   valjak(0.5,1.5,70);
   glPopMatrix();
   glRotated(135+gama,0,0,1);
   glTranslated(0,6.5,0);
   glRotated(delta,0,0,1);
   kvadar(5,1,1.5);
   glTranslated(6,0.5,0);
   poluvaljak(1,1.5,70);


}

void stanica(){
  glTranslated(0,0,5);
  prsten(10, 1.2,1,400);
  glTranslated(0,0,-2.5);
  valjak(1.0,5,100);
  glTranslated(0,0,-2.4);
  kugla(2.2,200,200);
  glTranslated(0,0,9.2);
  kugla(2.2,200,200);
  //glTranslated(0,0,2.8);
  glTranslated(0,0,-4.0);
  glRotated(90,0.0,1.0,0.0);
  glRotated(0+kut,1.0,0.0,0.0);
  valjak(0.5,9.0,100);
  glRotated(120,1.0,0.0,0.0);
  valjak(0.5,9.0,100);
  glRotated(120,1.0,0.0,0.0);
  valjak(0.5,9.0,100);
}

void svjetlo2() {
  float pozicija[] = {0.0f, 1.0f, 1.0f, 0.0f};
  // četvrti parametar postavljen na 1.0f definira "positional light"
  // na poziciji koju određuju prva tri parametra

  glLightfv(GL_LIGHT2, GL_DIFFUSE, crveno);
  glLightfv(GL_LIGHT2, GL_SPECULAR, crveno);
  glLightfv(GL_LIGHT2, GL_POSITION, pozicija);
} // svjetlo2

void lampa(){
  // kugla
  glTranslated(-13.0,0.0,0.0);
  kugla(2,500,500);

  //baza
  glMaterialfv(GL_FRONT, GL_DIFFUSE, sivo);
  glTranslated(20.0,0.0,0.0);
  valjak(5,0.5,100);
  glTranslated(0.0,0.0,0.5);
  valjak(2,0.25,100);
  glTranslated(0,1.5,0);
  glRotated(90,1.0,0.0,0.0);
  poluvaljak(1,3.5,100);
  //stupovi1
  glRotated(-90,1.0,0.0,0.0);
  glRotated(betta,0.0,1.0,0.0);
  glRotated(25,0.0,1.0,0.0);
  glTranslated(0.0,-0.5,0.0); 
  valjak(0.35,7,100);
  glTranslated(0.0,-2.5,0.0); 
  valjak(0.35,7,100);
  //spojnica1
  glTranslated(0.0,2.9,7.0);
  glRotated(-25,0.0,1.0,0.0);
  glRotated(90,1.0,0.0,0.0);
  valjak(0.4,3.5,100);
  //stupovi2
  glRotated(-90,1.0,0.0,0.0);
  glRotated(gama,0.0,1.0,0.0);
  glRotated(-55,0.0,1.0,0.0);
  glTranslated(0.0,-0.5,0.0); 
  valjak(0.35,7,100);
  glTranslated(0.0,-2.5,0.0); 
  valjak(0.35,7,100);
  //spojnica2
  glTranslated(0.0,2.9,7.0);
  glRotated(55,0.0,1.0,0.0);
  glRotated(90,1.0,0.0,0.0);
  valjak(0.4,3.5,100);
  //vrat
  glTranslated(0.0,0.0,1.7);
  glRotated(-90,1.0,0.0,0.0);
  glRotated(delta,0.0,1.0,0.0);
  glRotated(-35,0.0,1.0,0.0);
  valjak(0.4,2.0,100);
  //vrh
  glRotated(epsilon,0.0,0.0,1.0);
  glTranslated(0.0,0.0,2.5);
  glRotated(90,0.0,1.0,0.0);
  valjak(0.85,2.0,100);
  //stozac
  glTranslated(0.0,0.0,-1.5);
  stozac2(2,2.5,300);
 //svjetlo
  svjetlo2();
  // položaj svjetla 0 označit ćemo bijelom kockicom
  glMaterialfv(GL_FRONT, GL_EMISSION, crveno);
  //glTranslated(2.0,0.0,12.0);
  kugla(0.8,200,200);
  glMaterialfv(GL_FRONT, GL_EMISSION, crno);
  
  
}

void svjetlo0() {
  float pozicija[] = {0.0f, 0.0f, 0.0f, 1.0f};
  // četvrti parametar postavljen na 1.0f definira "positional light"
  // na poziciji koju određuju prva tri parametra

  glLightfv(GL_LIGHT0, GL_DIFFUSE, bijelo);
  glLightfv(GL_LIGHT0, GL_SPECULAR, bijelo);
  glLightfv(GL_LIGHT0, GL_POSITION, pozicija);
} // svjetlo0

void svjetlo1() {
  float pozicija[] = {0.0f, 0.0f, 1.0f, 0.0f};
  // četvrti parametar postavljen na 1.0f definira "positional light"
  // na poziciji koju određuju prva tri parametra

  glLightfv(GL_LIGHT1, GL_DIFFUSE, zuto);
  glLightfv(GL_LIGHT1, GL_SPECULAR, zuto);
  glLightfv(GL_LIGHT1, GL_POSITION, pozicija);
} // svjetlo1




void iscrtaj(void) {
  double r = 6.0;
  double h = 20; 
  double n = 20;

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //glColor3d(1.0, 1.0, 0.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  //gluLookAt(35.0, 0.0, 25.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
  // kamera gleda pola visine stošca iznad ishodišta
  gluLookAt(0.0, 30.0, 20.0, 0.0, 0.0, h/4.0 , 0.0, 0.0, 1.0);

  glPushMatrix(); // pamtimo da smo u ishodištu
    // postavljamo svjetlo 0 na odgovarajuću poziciju
    glTranslated(8.0, 20.0, 8.0);
    //glRotated (270.0,1.0,0.0,0.0);
    //glTranslated(0,0,9.2);

    svjetlo0();
    // položaj svjetla 0 označit ćemo bijelom kockicom
    glMaterialfv(GL_FRONT, GL_EMISSION, bijelo);
    //kugla(2.2,200,200);
    kocka(0.5);
    glMaterialfv(GL_FRONT, GL_EMISSION, crno);
  glPopMatrix(); // vraćamo se u ishodište

/*  glPushMatrix(); // pamtimo da smo u ishodištu
    // postavljamo svjetlo 1 na odgovarajuću poziciju
    glTranslated(0,0,9.2);

    svjetlo1();
    // položaj svjetla 0 označit ćemo bijelom kockicom
    glMaterialfv(GL_FRONT, GL_EMISSION, zuto);
    kugla(2.2,200,200);
    glMaterialfv(GL_FRONT, GL_EMISSION, crno);
  glPopMatrix(); // vraćamo se u ishodište
*/


  // rotacija stošca oko osi koja prolazi kroz plašt
  //glTranslated(0.0, r, 0.0);
  //glRotated(kut, 0.0, -r, h);
  //glTranslated(0.0, -r, 0.0);
  
  // rotaija oko sve 3 osi
  //glRotated(kut, 0.0, 0.0, 1.0);
  //glRotated(kut, 0.0, 1.0, 0.0);
  //glRotated(kut, 1.0, 0.0, 0.0);

  glMaterialfv(GL_FRONT, GL_DIFFUSE, zuto);
  glMaterialfv(GL_FRONT, GL_SPECULAR, bijelo);
  glMaterialf(GL_FRONT, GL_SHININESS, 20.0);
  
  //glTranslated(d, d, d);
  //stozac2(r,h,n);
  //valjak(r,h,n);
  
  //glEnable(GL_CULL_FACE);
  //kugla(r,h,n);  
  //polukugla(r,h,n);
  //elipsoida(8,4,2,h,n);
  //kvadar (5,2,4);
  //bager();
  //stanica();  
  lampa();

  glutSwapBuffers();
} // iscrtaj

void skaliraj(int w, int h) {
  double xmin = -10.0, xmax = 10.0;
  double xrange = xmax - xmin;
  double yrange = h * xrange / w;

  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(xmin, xmax, -yrange / 2.0, yrange / 2.0, 20.0, 50.0);
} // skaliraj

void rotiraj(void) {
   kut += 2.0;
   glutPostRedisplay();
} // rotiraj

void rotirajmin(void) {
   kut -= 2.0;
   glutPostRedisplay();
} // rotiraj

void tipka(unsigned char c, int x, int y) {
  if(c == 'q') exit(0);
  if(c == 's') glShadeModel(GL_SMOOTH); // glatko sjenčanje
  if(c == 'f') glShadeModel(GL_FLAT); // ravnomjerno sjenčanje
  if(c == 'B') glCullFace(GL_BACK); // odbaciti poligone koje gledamo u stražnju stranu 
  if(c == 'b') glCullFace(GL_FRONT); // odbaciti poligone koje gledamu u prednju stranu
  if(c == 'C') glEnable(GL_CULL_FACE); // uključivanje selektivnog odbacivanja
  if(c == 'c') glDisable(GL_CULL_FACE); // isključivanje selektivnog odbacivanja
  if(c == 'D') glEnable(GL_DEPTH_TEST); // uključivanje testiranja dubine
  if(c == 'd') glDisable(GL_DEPTH_TEST); // isključivanje testiranja dubine
  if(c == '0') glEnable(GL_LIGHT0);
  if(c == '=') glDisable(GL_LIGHT0);
  //if(c == 'v') { if(++verzija > 3) verzija = 0; }
  if(c == '1') { if(++betta > 20) betta = 20; }
  if(c == '2') { if(--betta < -20) betta = -20; }
  if(c == '3') { if(++gama > 20) gama = 20; }
  if(c == '4') { if(--gama < -20) gama = -20; }
  if(c == '5') { if(++delta > 20) delta = 20; }
  if(c == '6') { if(--delta < -20) delta = -20; }
  if(c == '7') { if(++epsilon > 20) epsilon = 20; }
  if(c == '8') { if(--epsilon < -20) epsilon = -20; }
} // tipka



void rotirajT(int id)
{
  kut += 0.05;
  glutPostRedisplay();
  // čekaj 50 milisekundi i ponovo pozovi rotirajT
  glutTimerFunc(50, rotirajT, 0);
} // rotirajT

int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);

  glutInitWindowSize(800, 600);
  glutCreateWindow("slika");

  glShadeModel(GL_FLAT);
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0, 0.0, 0.0, 0.0);

  glEnable(GL_LIGHTING); // omogućava osvjetljavanje
  glEnable(GL_LIGHT0); // uključuje svjetlo 0

  glutDisplayFunc(iscrtaj);
  glutReshapeFunc(skaliraj);
  glutKeyboardFunc(tipka);
  //glutIdleFunc(rotiraj);
  glutTimerFunc(50, rotirajT, 0); // prvi poziv rutine rotirajT

  glutMainLoop();
  return 0;
} // main
