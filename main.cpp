#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>

using namespace std;

class Field{
protected:
    double *value = nullptr;

    double magnitude() const {
        const double x = this->value[0];
        const double y = this->value[1];
        const double z = this->value[2];

        return sqrt(x*x + y*y + z*z);
    }

public:
    ~Field()= default;


    explicit Field(){
        this->value = (double*) malloc(sizeof(double)*3);
        this->value[0] = 0;
        this->value[1] = 0;
        this->value[2] = 0;
    }

    explicit Field (double x, double y, double z){
        this->value = static_cast<double *> (malloc(sizeof(double) * 3));
        this->value[0] = x;
        this->value[1] = y;
        this->value[2] = z;
    }

    void printMagnitude() const {
        double x = this->value[0];
        double y = this->value[1];
        double z = this->value[2];
      cout << "x: " << x << " y: " << y << " z: " << z;
    }



};

class ElectricField:Field {
private:
    double ElectricCharge = 0;
    double radius = 1;

public:
    explicit ElectricField():Field(){}
    explicit ElectricField(double x, double y, double z):Field(x,y,z){}
    ~ElectricField()= default;

    void setElectricCharge(const double ElectricCharge){
        this->ElectricCharge = ElectricCharge;
    }
    void setRadius(const double radius){
        this->radius = radius;
    }

    double electricField() const {
        const double t0 = 8.8541878128*pow(10,-12);
        return ElectricCharge/(4* M_PI *radius*radius*t0);
    }

    static double electricField( double ElectricCharge,double radius) {
        const double t0 = 8.8541878128*pow(10,-12);
        return ElectricCharge/(4* M_PI *radius*radius*t0);
    }

    ElectricField operator+(ElectricField e2) const {

        const double x = this->value[0] + e2.value[0];
        const double y = this->value[1] + e2.value[1];
        const double z = this->value[2] + e2.value[2];
        ElectricField e3(x,y,z);
        return e3;
    }

    friend ostream& operator<<(ostream& os, const ElectricField& obj);
};

class MagneticField:Field{
private:
  double Current = 0;
  double radius = 1;

public:
  ~MagneticField()= default;
  explicit MagneticField():Field(){}
  explicit MagneticField(double x, double y, double z):Field(x,y,z){}

  void setCurrent(const double Current){
      this->Current = Current;
  }
  void setRadius(const double radius){
      this->radius = radius;
  }

  double magneticField() const {
      const double µ0 = 1.25663706127*pow(10,-6);
      return Current/(2* M_PI *radius* µ0);
  }

  static double magneticField( double Current,double radius) {
      const double µ0 = 1.25663706127*pow(10,-6);
      return Current/(2* M_PI *radius* µ0);
  }

  MagneticField operator+(MagneticField m2) {

      const double x = this->value[0] + m2.value[0];
      const double y = this->value[1] + m2.value[1];
      const double z = this->value[2] + m2.value[2];
      MagneticField m3(x,y,z);
      return m3;
  }
    friend ostream& operator<<(ostream& os, const MagneticField& obj);
};

ostream& operator<<(ostream& os, const MagneticField& obj) {
    os << "radius: " << obj.radius << " current: " << obj.Current << " ";
    obj.printMagnitude();
    return os;
}

ostream& operator<<(ostream& os, const ElectricField& obj) {
    cout << "radius : " <<  obj.radius << " electric field: " << obj.ElectricCharge<<" ";
    obj.printMagnitude();
    return os;
}




int main(){
    ElectricField e1(1,2,3);
    cout << e1 << endl;
    ElectricField e2(20,30,61);
    cout << e2 << endl;
    ElectricField e3 = e1+e2;
    e3.setRadius(4);
    e3.setElectricCharge(2);
    cout << e3 << " E:"<< e3.electricField()<< endl << endl;

    MagneticField m1(1,2,3);
    m1.setCurrent(2);
    m1.setRadius(0.5);
    cout << m1 << " B: " << m1.magneticField() <<endl;

    MagneticField m2(2,3,4);


    MagneticField m3 = m2+m1;
    cout << m3 << endl;




    return 0;
}
