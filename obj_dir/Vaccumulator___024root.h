// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vaccumulator.h for the primary calling header

#ifndef VERILATED_VACCUMULATOR___024ROOT_H_
#define VERILATED_VACCUMULATOR___024ROOT_H_  // guard

#include "verilated.h"


class Vaccumulator__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vaccumulator___024root final {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(A,3,0);
    VL_OUT8(S,5,0);
    VL_OUT8(overflow,0,0);
    CData/*0:0*/ accumulator__DOT__c0;
    CData/*5:0*/ accumulator__DOT__sum;
    CData/*0:0*/ accumulator__DOT__ra__DOT__a3__DOT__Cin;
    CData/*0:0*/ accumulator__DOT__ra__DOT__a2__DOT__Cin;
    CData/*0:0*/ accumulator__DOT__ra__DOT__a1__DOT__Cin;
    CData/*3:0*/ __VdfgRegularize_hebeb780c_0_0;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VstlPhaseResult;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*3:0*/ __Vtrigprevexpr___TOP__A__0;
    CData/*0:0*/ __VicoDidInit;
    CData/*0:0*/ __VicoPhaseResult;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__1;
    CData/*0:0*/ __VactPhaseResult;
    CData/*0:0*/ __VnbaPhaseResult;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<QData/*63:0*/, 1> __VstlTriggered;
    VlUnpacked<QData/*63:0*/, 2> __VicoTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VactTriggered;
    VlUnpacked<QData/*63:0*/, 1> __VnbaTriggered;
    VlUnpacked<CData/*0:0*/, 3> __Vm_traceActivity;

    // INTERNAL VARIABLES
    Vaccumulator__Syms* vlSymsp;
    const char* vlNamep;

    // CONSTRUCTORS
    Vaccumulator___024root(Vaccumulator__Syms* symsp, const char* namep);
    ~Vaccumulator___024root();
    VL_UNCOPYABLE(Vaccumulator___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
