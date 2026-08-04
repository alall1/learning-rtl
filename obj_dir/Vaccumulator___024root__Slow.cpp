// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccumulator.h for the primary calling header

#include "Vaccumulator__pch.h"

void Vaccumulator___024root___ctor_var_reset(Vaccumulator___024root* vlSelf);

Vaccumulator___024root::Vaccumulator___024root(Vaccumulator__Syms* symsp, const char* namep)
 {
    vlSymsp = symsp;
    vlNamep = strdup(namep);
    // Reset structure values
    Vaccumulator___024root___ctor_var_reset(this);
}

void Vaccumulator___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vaccumulator___024root::~Vaccumulator___024root() {
    VL_DO_DANGLING(std::free(const_cast<char*>(vlNamep)), vlNamep);
}
