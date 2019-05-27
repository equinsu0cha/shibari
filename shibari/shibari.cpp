#include "stdafx.h"
#include "shibari.h"



shibari::shibari() 
 : main_module(0){}

shibari::~shibari() 
{}

shibari_linker_errors shibari::exec_shibari(uint32_t enma_build_flags, std::vector<uint8_t>& out_image) {

    shibari_linker_errors linker_ret = shibari_linker(extended_modules, main_module).link_modules();

    if (linker_ret != shibari_linker_errors::shibari_linker_ok) {
        return linker_ret;
    }

    return build_shibari_image(main_module->get_module_image(),
        PE_IMAGE_BUILD_ALL_DIRECTORIES | enma_build_flags,
        out_image) ? shibari_linker_ok : shibari_linker_error_build;
}


void shibari::set_main_module(shibari_module* module) {
    if (module) {
        this->main_module = module;
    }
}

void shibari::add_extended_module(shibari_module* module) {
    if (module) {
        this->extended_modules.push_back(module);
    }
}

std::vector<shibari_module*>& shibari::get_extended_modules() {
    return this->extended_modules;
}

const std::vector<shibari_module*>& shibari::get_extended_modules() const {
    return this->extended_modules;
}

shibari_module* shibari::get_main_module() {
    return this->main_module;
}

const shibari_module* shibari::get_main_module() const {
    return this->main_module;
}