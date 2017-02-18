#include <systemc.h>
// #include <iostream>


SC_MODULE(dflipflop) {
	// sc_in< sc_uint<1> > a, b;
	// sc_out< sc_uint<1> > f;
  
  sc_in<bool> din1;
  sc_in<bool> din2;
	sc_in<bool> clock;
  sc_out<bool> f;
  // sc_out<bool> dout;



	void printSum() {
    // dout = din;
    f.write(din1.read() & din2.read());
	}


	SC_CTOR(dflipflop) {
		SC_METHOD(printSum);
		sensitive << clock.pos();
	
	}
};

SC_MODULE(stimuli) {

  sc_in<bool> clock;
  sc_out<bool> din1;
  sc_out<bool> din2;

  bool data1;
  bool data2;
  void stimgen();

  SC_CTOR(stimuli) {
    SC_THREAD(stimgen);
    sensitive << clock.neg();
    data1 = false;
    data2 = true;
  }
};

void stimuli::stimgen() {
  while(true) {
    wait();
    wait();
    data1 = data2^1;
    data2 = data2^1;
    din1 = data1;
    din2 = data2;
  }

}

SC_MODULE(display) {

  sc_in<bool> clock;
  sc_in<bool> din1;
  sc_in<bool> din2;
  sc_in<bool> f;
  // sc_in<bool> dout;

  void output();

  SC_CTOR(display) {
    SC_METHOD(output);
    sensitive << clock << f << din1 << din2;
  }
};

void display::output() {
  std::cout << sc_time_stamp()
            << ": din1=" << din1
            << ": din2=" << din2
            << ": dout=" << f
            << ": clck=" << clock
            << "\n";
}

int sc_main(int argc, char* argv[]) {

  dflipflop dff("DFliptflop");
  stimuli stim("stimulation");
  display dis("display");

  sc_signal<bool> din1;
  sc_signal<bool> din2;
  sc_signal<bool> f;
  sc_clock clock("clock", 50, SC_NS, 0.5, 25, SC_NS);


  dff.din1(din1);
  dff.din2(din2);
  dff.f(f);
  dff.clock(clock);

  stim.din1(din1);
  stim.din2(din2);
  stim.clock(clock);

  dis.din1(din1);
  dis.din2(din2);
  dis.f(f);
  dis.clock(clock);


  sc_start(400, SC_NS);


  
  return 0;
}
