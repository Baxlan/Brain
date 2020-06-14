// Activation.hh

#ifndef OMNILEARN_ACTIVATION_HH_
#define OMNILEARN_ACTIVATION_HH_

#include <map>
#include <memory>
#include <string>

#include "Matrix.hh"



namespace omnilearn
{



enum class Activation {Linear, Sigmoid, Tanh, Softplus, Relu, Prelu, Elu, Pelu, Srelu, Gauss, Pgauss, Softexp, Psoftexp, Sin, Sinc};



// interface
class IActivation
{
public:
    virtual ~IActivation(){}
    virtual double activate(double val) const = 0;
    virtual double prime(double val) const = 0;
    virtual void computeGradients(double aggr, double inputGrad) = 0;
    virtual void updateCoefs(double learningRate) = 0;
    virtual void setCoefs(Vector const& coefs) = 0;
    virtual rowVector getCoefs() const = 0;
    virtual Activation signature() const = 0;
    virtual void keep() = 0;
    virtual void release() = 0;
    virtual void nesterov() = 0;
};



class Linear : public IActivation
{
public:
    Linear(Vector const& coefs = Vector());
    double activate(double val) const;
    double prime(double val) const;
    void computeGradients(double aggr, double inputGrad);
    void updateCoefs(double learningRate);
    void setCoefs(Vector const& coefs);
    rowVector getCoefs() const;
    Activation signature() const;
    void keep();
    void release();
    void nesterov();
};



class Sigmoid : public IActivation
{
public:
    Sigmoid(Vector const& coefs = Vector());
    double activate(double val) const;
    double prime(double val) const;
    void computeGradients(double aggr, double inputGrad);
    void updateCoefs(double learningRate);
    void setCoefs(Vector const& coefs);
    rowVector getCoefs() const;
    Activation signature() const;
    void keep();
    void release();
    void nesterov();
};



class  Tanh : public IActivation
{
public:
    Tanh(Vector const& coefs = Vector());
    double activate(double val) const;
    double prime(double val) const;
    void computeGradients(double aggr, double inputGrad);
    void updateCoefs(double learningRate);
    void setCoefs(Vector const& coefs);
    rowVector getCoefs() const;
    Activation signature() const;
    void keep();
    void release();
    void nesterov();
};



class Softplus : public IActivation
{
public:
    Softplus(Vector const& coefs = Vector());
    double activate(double val) const;
    double prime(double val) const;
    void computeGradients(double aggr, double inputGrad);
    void updateCoefs(double learningRate);
    void setCoefs(Vector const& coefs);
    rowVector getCoefs() const;
    Activation signature() const;
    void keep();
    void release();
    void nesterov();
};



class Relu : public IActivation
{
public:
    Relu(Vector const& coefs = (Vector(1) << 0.01).finished());
    double activate(double val) const;
    double prime(double val) const;
    void computeGradients(double aggr, double inputGrad);
    void updateCoefs(double learningRate);
    void setCoefs(Vector const& coefs);
    rowVector getCoefs() const;
    Activation signature() const;
    void keep();
    void release();
    void nesterov();

protected:
    double _coef;
    double _savedCoef;
};



class Prelu : public Relu
{
public:
    Prelu(Vector const& coefs = (Vector(1) << 0.01).finished());
    void computeGradients(double aggr, double inputGrad);
    void updateCoefs(double learningRate);
    Activation signature() const;
    void nesterov();

protected:
    double _coefGradient;
    double _counter;
};



class Elu : public IActivation
{
public:
    Elu(Vector const& coefs = (Vector(1) << 0.01).finished());
    double activate(double val) const;
    double prime(double val) const;
    void computeGradients(double aggr, double inputGrad);
    void updateCoefs(double learningRate);
    void setCoefs(Vector const& coefs);
    rowVector getCoefs() const;
    Activation signature() const;
    void keep();
    void release();
    void nesterov();

protected:
    double _coef;
    double _savedCoef;
};



class Pelu : public Elu
{
public:
    Pelu(Vector const& coefs = (Vector(1) << 0.01).finished());
    void computeGradients(double aggr, double inputGrad);
    void updateCoefs(double learningRate);
    Activation signature() const;
    void nesterov();
};



class Srelu : public IActivation
{
public:
    Srelu(Vector const& coefs = (Vector(4) << 0.1, 0.1, -1.0, 1.0).finished());
    double activate(double val) const;
    double prime(double val) const;
    void computeGradients(double aggr, double inputGrad);
    void updateCoefs(double learningRate);
    void setCoefs(Vector const& coefs);
    rowVector getCoefs() const;
    Activation signature() const;
    void keep();
    void release();
    void nesterov();

protected:
    double _coef1;
    double _coef2;
    double _hinge1;
    double _hinge2;

    double _savedCoef1;
    double _savedCoef2;
    double _savedHinge1;
    double _savedHinge2;
};



class Gauss : public IActivation
{
public:
    Gauss(Vector const& coefs = (Vector(3) << 0.0, 1.0, 1.0).finished()); // should take mean and deviation, and make a parametric version
    double activate(double val) const;
    double prime(double val) const;
    void computeGradients(double aggr, double inputGrad);
    void updateCoefs(double learningRate);
    void setCoefs(Vector const& coefs);
    rowVector getCoefs() const;
    Activation signature() const;
    void keep();
    void release();
    void nesterov();

protected:
    double _center;
    double _dev;
    double _coef;
    double _savedCenter;
    double _savedDev;
    double _savedCoef;
};



class Pgauss : public Gauss
{
public:
    Pgauss(Vector const& coefs = (Vector(3) << 0, 1, 1).finished());
    void computeGradients(double aggr, double inputGrad);
    void updateCoefs(double learningRate);
    Activation signature() const;
    void nesterov();
};



class Softexp : public IActivation
{
public:
    Softexp(Vector const& coefs = (Vector(1) << 0.5).finished());
    double activate(double val) const;
    double prime(double val) const;
    void computeGradients(double aggr, double inputGrad);
    void updateCoefs(double learningRate);
    void setCoefs(Vector const& coefs);
    rowVector getCoefs() const;
    Activation signature() const;
    void keep();
    void release();
    void nesterov();

protected:
    double _coef;
    double _savedCoef;
};



class Psoftexp : public Softexp
{
public:
    Psoftexp(Vector const& coefs = (Vector(1) << 0.5).finished());
    void computeGradients(double aggr, double inputGrad);
    void updateCoefs(double learningRate);
    Activation signature() const;
    void nesterov();
};



class Sin : public IActivation
{
public:
    Sin(Vector const& coefs = Vector());
    double activate(double val) const;
    double prime(double val) const;
    void computeGradients(double aggr, double inputGrad);
    void updateCoefs(double learningRate);
    void setCoefs(Vector const& coefs);
    rowVector getCoefs() const;
    Activation signature() const;
    void keep();
    void release();
    void nesterov();
};



class Sinc : public IActivation
{
public:
    Sinc(Vector const& coefs = Vector());
    double activate(double val) const;
    double prime(double val) const;
    void computeGradients(double aggr, double inputGrad);
    void updateCoefs(double learningRate);
    void setCoefs(Vector const& coefs);
    rowVector getCoefs() const;
    Activation signature() const;
    void keep();
    void release();
    void nesterov();
};



Vector singleSoftmax(Vector input);
Matrix softmax(Matrix inputs);



static std::map<Activation, std::function<std::unique_ptr<IActivation>()>> activationMap = {
    {Activation::Linear, []{return std::make_unique<Linear>();}},
    {Activation::Sigmoid, []{return std::make_unique<Sigmoid>();}},
    {Activation::Tanh, []{return std::make_unique<Tanh>();}},
    {Activation::Softplus, []{return std::make_unique<Softplus>();}},
    {Activation::Relu, []{return std::make_unique<Relu>();}},
    {Activation::Prelu, []{return std::make_unique<Prelu>();}},
    {Activation::Elu, []{return std::make_unique<Elu>();}},
    {Activation::Pelu, []{return std::make_unique<Pelu>();}},
    {Activation::Srelu, []{return std::make_unique<Srelu>();}},
    {Activation::Gauss, []{return std::make_unique<Gauss>();}},
    {Activation::Pgauss, []{return std::make_unique<Pgauss>();}},
    {Activation::Softexp, []{return std::make_unique<Softexp>();}},
    {Activation::Psoftexp, []{return std::make_unique<Psoftexp>();}},
    {Activation::Sin, []{return std::make_unique<Sin>();}},
    {Activation::Sinc, []{return std::make_unique<Sinc>();}}
};



static std::map<std::string, Activation> stringToActivationMap = {
    {"linear", Activation::Linear},
    {"sigmoid", Activation::Sigmoid},
    {"tanh", Activation::Tanh},
    {"softplus", Activation::Softplus},
    {"relu", Activation::Relu},
    {"prelu", Activation::Prelu},
    {"elu", Activation::Elu},
    {"pelu", Activation::Pelu},
    {"srelu", Activation::Srelu},
    {"gauss", Activation::Gauss},
    {"pgauss", Activation::Pgauss},
    {"softexp", Activation::Softexp},
    {"psoftexp", Activation::Psoftexp},
    {"sin", Activation::Sin},
    {"sinc", Activation::Sinc}
};



static std::map<Activation, std::string> activationToStringMap = {
    {Activation::Linear, "linear"},
    {Activation::Sigmoid, "sigmoid"},
    {Activation::Tanh, "tanh"},
    {Activation::Softplus, "softplus"},
    {Activation::Relu, "relu"},
    {Activation::Prelu, "prelu"},
    {Activation::Elu, "elu"},
    {Activation::Pelu, "pelu"},
    {Activation::Srelu, "srelu"},
    {Activation::Gauss, "gauss"},
    {Activation::Pgauss, "pgauss"},
    {Activation::Softexp, "softexp"},
    {Activation::Psoftexp, "psoftexp"},
    {Activation::Sin, "sin"},
    {Activation::Sinc, "sinc"}
};



} //namespace omnilearn



#endif //OMNILEARN_ACTIVATION_HH_