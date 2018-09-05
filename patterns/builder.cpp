#include <iostream>
#include <string>
#include <map>

using namespace std;

//the product class

class Device
{
public:
  Device(const string &deviceType): deviceType_(deviceType)
  {
  }

  void setParameter(const string &parameterName, const string &parameterValue)
  {
    parameter_[parameterName] = parameterValue;
  }

  const string& getParameterValue(const string &parameterName)
  {
    map<string, string>::const_iterator it;
    it = parameter_.find(parameterName);
    if(it != parameter_.end())
      return it->second;
    else
      {
	parameter_[parameterName] = "Not found!";
	return parameter_[parameterName];
      }
  }

  void const show(void)
  {
    cout << "\n-------------------------------" << endl;
    cout << "Device type: " << deviceType_ << endl;
    cout << "Screen size: " << parameter_["Screen_size"] << endl;
    cout << "Brand: " << parameter_["Brand"] << endl;
    cout << "RAM: " << parameter_["RAM"] << endl;
    cout << "Hard disk size: " << parameter_["Hard_disk_size"] << endl;
    cout << "Processor type: " << parameter_["Processor_type"] << endl;
    cout << "GPU: " << parameter_["GPU"] << endl;
  }

private:
  Device();
  string deviceType_;
  map<string, string> parameter_;
};

//abstract 'Builder' class
class deviceBuilder
{
public:
  deviceBuilder()
  {
    device = NULL;
  }
  virtual ~deviceBuilder()
  {
    if(device)
      {
	delete device;
	device = NULL;
      }
  }

  const Device &getDevice(void)
  {
    return *device;
  }

  virtual void buildScreen() = 0;
  virtual void buildBrand() = 0;
  virtual void buildRAM() = 0;
  virtual void buildHardDisk() = 0;
  virtual void buildProcessor() = 0;
  virtual void buildGPU() = 0;

protected:
  Device *device;
};

//concrete 'Builder' class #1
class laptopBuilder : public deviceBuilder
{
public:
  laptopBuilder()
  {
    device = new Device("Laptop");
  }

  void buildScreen()
  {
    device->setParameter("Screen_size", "15.6'");
  }

  void buildBrand()
  {
    device->setParameter("Brand", "Lenovo");
  }

  void buildRAM()
  {
    device->setParameter("RAM", "16 GB");
  }

  void buildHardDisk()
  {
    device->setParameter("Hard_disk_size", "1 TB SSD");
  }

  void buildProcessor()
  {
    device->setParameter("Processor_type", "Intel core i7");
  }

  void buildGPU()
  {
    device->setParameter("GPU", "GeForce GTX1070 8 GB");
  }
};

//concrete 'Builder' class #2
class tabletBuilder : public deviceBuilder
{
public:
  tabletBuilder()
  {
    device = new Device("Tablet");
  }

  void buildScreen()
  {
    device->setParameter("Screen_size", "8'");
  }

  void buildBrand()
  {
    device->setParameter("Brand", "Asus");
  }

  void buildRAM()
  {
    device->setParameter("RAM", "4 GB");
  }

  void buildHardDisk()
  {
    device->setParameter("Hard_disk_size", "128 GB ");
  }

  void buildProcessor()
  {
    device->setParameter("Processor_type", "Intel celeron");
  }

  void buildGPU()
  {
    device->setParameter("GPU", "Nvidia Tegra X1");
  }
};

//concrete 'Builder' class #3
class smartphoneBuilder : public deviceBuilder
{
public:
  smartphoneBuilder()
  {
    device = new Device("Smartphone");
  }

  void buildScreen()
  {
    device->setParameter("Screen_size", "5.5'");
  }

  void buildBrand()
  {
    device->setParameter("Brand", "LG");
  }

  void buildRAM()
  {
    device->setParameter("RAM", "4 GB");
  }

  void buildHardDisk()
  {
    device->setParameter("Hard_disk_size", "64 GB ");
  }

  void buildProcessor()
  {
    device->setParameter("Processor_type", "Snapdragon 835");
  }

  void buildGPU()
  {
    device->setParameter("GPU", "Qualcomm Adreno");
  }
};

class Chooser
{
public:
  void construct(deviceBuilder *devBuilder)
  {
    devBuilder->buildScreen();
    devBuilder->buildBrand();
    devBuilder->buildRAM();
    devBuilder->buildHardDisk();
    devBuilder->buildProcessor();
    devBuilder->buildGPU();
  }
};

int main()
{
  deviceBuilder *builder = NULL;
  Chooser chooser;

  builder = new laptopBuilder();
  chooser.construct(builder);
  (const_cast<Device&>(builder->getDevice())).show();
  delete builder;

  builder = new tabletBuilder();
  chooser.construct(builder);
  (const_cast<Device&>(builder->getDevice())).show();
  delete builder;

  builder = new smartphoneBuilder();
  chooser.construct(builder);
  (const_cast<Device&>(builder->getDevice())).show();
  delete builder;

  return 0;
}
