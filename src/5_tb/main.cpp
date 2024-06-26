#include <exception>
#include <iostream>
#include <systemc>

#include "cactus_ver.h"
#include "cclight_new.h"
#include "global_counter.h"
#include "global_json.h"
#include "logger_wrapper.h"
#include "q_data_type.h"
#include "tb_qvm.h"

//#include "../../../simbricks_pcie_dma/accel-sim/plumbing.h"
#include "accel-sim/plumbing.h"
#include "common/common.h"

using namespace cactus;

int sc_main(int argc, char* argv[]) {

	main_for_CACTUS(argc,argv);
    // The following command turns off warning about IEEE 1666 deprecated features.
    sc_core::sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", sc_core::SC_DO_NOTHING);

    Global_config& global_config = Global_config::get_instance();
    global_config.init_cmdparser(argc, argv);
	dprintf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    global_config.run_cmdparser();

	dprintf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    std::cout << "Control Architecture Simulator, " << CACTUS_VERSION << std::endl;
    std::cout << "Simulation Starts." << std::endl;

	dprintf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
    sc_clock clock_200MHz("clock_200MHz", 2.0, sc_core::SC_NS, 0.5);
    sc_clock clock_50MHz("clock_50MHz", 20.0, sc_core::SC_NS, 0.5);

    // CC_Light_TB tb("cclight_tb", global_config,  num_sim_cycles);
    QVM_TB tb("qvm_tb", global_config.num_sim_cycles);
	dprintf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

    tb.clock_200MHz(clock_200MHz);
    tb.clock_50MHz(clock_50MHz);

	dprintf("sc start.");
    try {
        sc_start();
    } catch (std::exception& e) {
		eprintf("sc start error.");
        std::cerr << e.what() << std::endl;
    }

	dprintf("sc end.");
    // dump data memory
    if (!global_config.data_mem_dump_fn.empty()) {
        global_config.data_memory->dump(global_config.data_mem_dump_fn);
    }

    // system("pause");
    return 0;
}
