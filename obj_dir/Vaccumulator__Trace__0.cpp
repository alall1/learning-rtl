// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vaccumulator__Syms.h"


void Vaccumulator___024root__trace_chg_0_sub_0(Vaccumulator___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vaccumulator___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccumulator___024root__trace_chg_0\n"); );
    // Body
    Vaccumulator___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaccumulator___024root*>(voidSelf);
    Vaccumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    Vaccumulator___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vaccumulator___024root__trace_chg_0_sub_0(Vaccumulator___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccumulator___024root__trace_chg_0_sub_0\n"); );
    Vaccumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 0);
    if (VL_UNLIKELY(((vlSelfRef.__Vm_traceActivity[1U] 
                      | vlSelfRef.__Vm_traceActivity[2U])))) {
        bufp->chgBit(oldp+0,(vlSelfRef.accumulator__DOT__c0));
        bufp->chgCData(oldp+1,((((((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a3__DOT__Cin) 
                                   ^ ((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0) 
                                      >> 3U)) << 3U) 
                                 | (4U & (((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a2__DOT__Cin) 
                                           << 2U) ^ 
                                          (0xfffffffcU 
                                           & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0))))) 
                                | ((2U & (((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a1__DOT__Cin) 
                                           << 1U) ^ 
                                          (0xfffffffeU 
                                           & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)))) 
                                   | (1U & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0))))),4);
        bufp->chgBit(oldp+2,(vlSelfRef.accumulator__DOT__ra__DOT__a1__DOT__Cin));
        bufp->chgBit(oldp+3,(vlSelfRef.accumulator__DOT__ra__DOT__a2__DOT__Cin));
        bufp->chgBit(oldp+4,(vlSelfRef.accumulator__DOT__ra__DOT__a3__DOT__Cin));
        bufp->chgBit(oldp+5,((1U & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0))));
        bufp->chgBit(oldp+6,((1U & ((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a1__DOT__Cin) 
                                    ^ ((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0) 
                                       >> 1U)))));
        bufp->chgBit(oldp+7,((1U & ((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a2__DOT__Cin) 
                                    ^ ((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0) 
                                       >> 2U)))));
        bufp->chgBit(oldp+8,(((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a3__DOT__Cin) 
                              ^ ((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0) 
                                 >> 3U))));
    }
    bufp->chgBit(oldp+9,(vlSelfRef.clk));
    bufp->chgCData(oldp+10,(vlSelfRef.A),4);
    bufp->chgCData(oldp+11,(vlSelfRef.S),6);
    bufp->chgBit(oldp+12,(vlSelfRef.overflow));
    bufp->chgBit(oldp+13,((((IData)(vlSelfRef.S) >> 4U) 
                           & (IData)(vlSelfRef.accumulator__DOT__c0))));
    bufp->chgBit(oldp+14,(((IData)(vlSelfRef.accumulator__DOT__c0) 
                           & (0x30U == (0x30U & (IData)(vlSelfRef.S))))));
    bufp->chgCData(oldp+15,(((((4U & ((0x1ffffffcU 
                                       & ((IData)(vlSelfRef.S) 
                                          >> 3U)) ^ 
                                      (0x3ffffffcU 
                                       & (((IData)(vlSelfRef.S) 
                                           >> 2U) & 
                                          ((IData)(vlSelfRef.accumulator__DOT__c0) 
                                           << 2U))))) 
                               | ((2U & ((0x1ffffffeU 
                                          & ((IData)(vlSelfRef.S) 
                                             >> 3U)) 
                                         ^ ((IData)(vlSelfRef.accumulator__DOT__c0) 
                                            << 1U))) 
                                  | ((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a3__DOT__Cin) 
                                     ^ ((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0) 
                                        >> 3U)))) << 3U) 
                             | ((4U & (((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a2__DOT__Cin) 
                                        << 2U) ^ (0xfffffffcU 
                                                  & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)))) 
                                | ((2U & (((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a1__DOT__Cin) 
                                           << 1U) ^ 
                                          (0xfffffffeU 
                                           & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)))) 
                                   | (1U & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)))))),6);
    bufp->chgBit(oldp+16,((1U & ((IData)(vlSelfRef.S) 
                                 >> 4U))));
    bufp->chgBit(oldp+17,((1U & (((IData)(vlSelfRef.S) 
                                  >> 4U) ^ (IData)(vlSelfRef.accumulator__DOT__c0)))));
    bufp->chgBit(oldp+18,((1U & ((IData)(vlSelfRef.S) 
                                 >> 5U))));
    bufp->chgBit(oldp+19,((1U & (((IData)(vlSelfRef.S) 
                                  >> 5U) ^ (((IData)(vlSelfRef.S) 
                                             >> 4U) 
                                            & (IData)(vlSelfRef.accumulator__DOT__c0))))));
    bufp->chgCData(oldp+20,((0x0000000fU & (IData)(vlSelfRef.S))),4);
    bufp->chgBit(oldp+21,((1U & (IData)(vlSelfRef.A))));
    bufp->chgBit(oldp+22,((1U & (IData)(vlSelfRef.S))));
    bufp->chgBit(oldp+23,((1U & ((IData)(vlSelfRef.A) 
                                 >> 1U))));
    bufp->chgBit(oldp+24,((1U & ((IData)(vlSelfRef.S) 
                                 >> 1U))));
    bufp->chgBit(oldp+25,((1U & ((IData)(vlSelfRef.A) 
                                 >> 2U))));
    bufp->chgBit(oldp+26,((1U & ((IData)(vlSelfRef.S) 
                                 >> 2U))));
    bufp->chgBit(oldp+27,((1U & ((IData)(vlSelfRef.A) 
                                 >> 3U))));
    bufp->chgBit(oldp+28,((1U & ((IData)(vlSelfRef.S) 
                                 >> 3U))));
}

void Vaccumulator___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccumulator___024root__trace_cleanup\n"); );
    // Body
    Vaccumulator___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaccumulator___024root*>(voidSelf);
    Vaccumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[2U] = 0U;
}
