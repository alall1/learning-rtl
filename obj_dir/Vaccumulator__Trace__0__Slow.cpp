// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals

#include "verilated_vcd_c.h"
#include "Vaccumulator__Syms.h"


VL_ATTR_COLD void Vaccumulator___024root__trace_init_sub__TOP__0(Vaccumulator___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccumulator___024root__trace_init_sub__TOP__0\n"); );
    Vaccumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const int c = vlSymsp->__Vm_baseCode;
    VL_TRACE_PUSH_PREFIX(tracep, "$rootio", VerilatedTracePrefixType::SCOPE_MODULE, 0, 0);
    VL_TRACE_DECL_BIT(tracep,c+9,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+10,0,"A",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BUS(tracep,c+11,0,"S",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 5,0);
    VL_TRACE_DECL_BIT(tracep,c+12,0,"overflow",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_POP_PREFIX(tracep);
    VL_TRACE_PUSH_PREFIX(tracep, "accumulator", VerilatedTracePrefixType::SCOPE_MODULE, 0, 0);
    VL_TRACE_DECL_BIT(tracep,c+9,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+10,0,"A",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BUS(tracep,c+11,0,"S",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 5,0);
    VL_TRACE_DECL_BIT(tracep,c+12,0,"overflow",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+0,0,"c0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+13,0,"c1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+14,0,"ovfl",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BUS(tracep,c+15,0,"sum",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, 5,0);
    VL_TRACE_PUSH_PREFIX(tracep, "ca0", VerilatedTracePrefixType::SCOPE_MODULE, 0, 0);
    VL_TRACE_DECL_BIT(tracep,c+0,0,"A",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+16,0,"B",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+29,0,"Cin",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+17,0,"S",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+13,0,"Cout",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_POP_PREFIX(tracep);
    VL_TRACE_PUSH_PREFIX(tracep, "ca1", VerilatedTracePrefixType::SCOPE_MODULE, 0, 0);
    VL_TRACE_DECL_BIT(tracep,c+13,0,"A",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+18,0,"B",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+29,0,"Cin",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+19,0,"S",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+14,0,"Cout",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_POP_PREFIX(tracep);
    VL_TRACE_PUSH_PREFIX(tracep, "ra", VerilatedTracePrefixType::SCOPE_MODULE, 0, 0);
    VL_TRACE_DECL_BUS(tracep,c+10,0,"A",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BUS(tracep,c+20,0,"B",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BUS(tracep,c+1,0,"S",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, 3,0);
    VL_TRACE_DECL_BIT(tracep,c+0,0,"Cout",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+2,0,"c0",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+3,0,"c1",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+4,0,"c2",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC);
    VL_TRACE_PUSH_PREFIX(tracep, "a0", VerilatedTracePrefixType::SCOPE_MODULE, 0, 0);
    VL_TRACE_DECL_BIT(tracep,c+21,0,"A",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+22,0,"B",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+29,0,"Cin",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+5,0,"S",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+2,0,"Cout",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_POP_PREFIX(tracep);
    VL_TRACE_PUSH_PREFIX(tracep, "a1", VerilatedTracePrefixType::SCOPE_MODULE, 0, 0);
    VL_TRACE_DECL_BIT(tracep,c+23,0,"A",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+24,0,"B",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+2,0,"Cin",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+6,0,"S",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+3,0,"Cout",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_POP_PREFIX(tracep);
    VL_TRACE_PUSH_PREFIX(tracep, "a2", VerilatedTracePrefixType::SCOPE_MODULE, 0, 0);
    VL_TRACE_DECL_BIT(tracep,c+25,0,"A",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+26,0,"B",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+3,0,"Cin",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+7,0,"S",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+4,0,"Cout",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_POP_PREFIX(tracep);
    VL_TRACE_PUSH_PREFIX(tracep, "a3", VerilatedTracePrefixType::SCOPE_MODULE, 0, 0);
    VL_TRACE_DECL_BIT(tracep,c+27,0,"A",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+28,0,"B",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+4,0,"Cin",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+8,0,"S",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_DECL_BIT(tracep,c+0,0,"Cout",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC);
    VL_TRACE_POP_PREFIX(tracep);
    VL_TRACE_POP_PREFIX(tracep);
    VL_TRACE_POP_PREFIX(tracep);
}

VL_ATTR_COLD void Vaccumulator___024root__trace_init_top(Vaccumulator___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccumulator___024root__trace_init_top\n"); );
    Vaccumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vaccumulator___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vaccumulator___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
VL_ATTR_COLD void Vaccumulator___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vaccumulator___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vaccumulator___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vaccumulator___024root__trace_register(Vaccumulator___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccumulator___024root__trace_register\n"); );
    Vaccumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&Vaccumulator___024root__trace_const_0, 0, vlSelf);
    tracep->addFullCb(&Vaccumulator___024root__trace_full_0, 0, vlSelf);
    tracep->addChgCb(&Vaccumulator___024root__trace_chg_0, 0, vlSelf);
    tracep->addCleanupCb(&Vaccumulator___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vaccumulator___024root__trace_const_0_sub_0(Vaccumulator___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vaccumulator___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccumulator___024root__trace_const_0\n"); );
    // Body
    Vaccumulator___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaccumulator___024root*>(voidSelf);
    Vaccumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vaccumulator___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vaccumulator___024root__trace_const_0_sub_0(Vaccumulator___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccumulator___024root__trace_const_0_sub_0\n"); );
    Vaccumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullBit(oldp+29,(0U));
}

VL_ATTR_COLD void Vaccumulator___024root__trace_full_0_sub_0(Vaccumulator___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vaccumulator___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccumulator___024root__trace_full_0\n"); );
    // Body
    Vaccumulator___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vaccumulator___024root*>(voidSelf);
    Vaccumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    Vaccumulator___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vaccumulator___024root__trace_full_0_sub_0(Vaccumulator___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccumulator___024root__trace_full_0_sub_0\n"); );
    Vaccumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    bufp->fullBit(oldp+0,(vlSelfRef.accumulator__DOT__c0));
    bufp->fullCData(oldp+1,((((((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a3__DOT__Cin) 
                                ^ ((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0) 
                                   >> 3U)) << 3U) | 
                              (4U & (((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a2__DOT__Cin) 
                                      << 2U) ^ (0xfffffffcU 
                                                & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0))))) 
                             | ((2U & (((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a1__DOT__Cin) 
                                        << 1U) ^ (0xfffffffeU 
                                                  & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)))) 
                                | (1U & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0))))),4);
    bufp->fullBit(oldp+2,(vlSelfRef.accumulator__DOT__ra__DOT__a1__DOT__Cin));
    bufp->fullBit(oldp+3,(vlSelfRef.accumulator__DOT__ra__DOT__a2__DOT__Cin));
    bufp->fullBit(oldp+4,(vlSelfRef.accumulator__DOT__ra__DOT__a3__DOT__Cin));
    bufp->fullBit(oldp+5,((1U & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0))));
    bufp->fullBit(oldp+6,((1U & ((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a1__DOT__Cin) 
                                 ^ ((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0) 
                                    >> 1U)))));
    bufp->fullBit(oldp+7,((1U & ((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a2__DOT__Cin) 
                                 ^ ((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0) 
                                    >> 2U)))));
    bufp->fullBit(oldp+8,(((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a3__DOT__Cin) 
                           ^ ((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0) 
                              >> 3U))));
    bufp->fullBit(oldp+9,(vlSelfRef.clk));
    bufp->fullCData(oldp+10,(vlSelfRef.A),4);
    bufp->fullCData(oldp+11,(vlSelfRef.S),6);
    bufp->fullBit(oldp+12,(vlSelfRef.overflow));
    bufp->fullBit(oldp+13,((((IData)(vlSelfRef.S) >> 4U) 
                            & (IData)(vlSelfRef.accumulator__DOT__c0))));
    bufp->fullBit(oldp+14,(((IData)(vlSelfRef.accumulator__DOT__c0) 
                            & (0x30U == (0x30U & (IData)(vlSelfRef.S))))));
    bufp->fullCData(oldp+15,(((((4U & ((0x1ffffffcU 
                                        & ((IData)(vlSelfRef.S) 
                                           >> 3U)) 
                                       ^ (0x3ffffffcU 
                                          & (((IData)(vlSelfRef.S) 
                                              >> 2U) 
                                             & ((IData)(vlSelfRef.accumulator__DOT__c0) 
                                                << 2U))))) 
                                | ((2U & ((0x1ffffffeU 
                                           & ((IData)(vlSelfRef.S) 
                                              >> 3U)) 
                                          ^ ((IData)(vlSelfRef.accumulator__DOT__c0) 
                                             << 1U))) 
                                   | ((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a3__DOT__Cin) 
                                      ^ ((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0) 
                                         >> 3U)))) 
                               << 3U) | ((4U & (((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a2__DOT__Cin) 
                                                 << 2U) 
                                                ^ (0xfffffffcU 
                                                   & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)))) 
                                         | ((2U & (
                                                   ((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a1__DOT__Cin) 
                                                    << 1U) 
                                                   ^ 
                                                   (0xfffffffeU 
                                                    & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)))) 
                                            | (1U & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)))))),6);
    bufp->fullBit(oldp+16,((1U & ((IData)(vlSelfRef.S) 
                                  >> 4U))));
    bufp->fullBit(oldp+17,((1U & (((IData)(vlSelfRef.S) 
                                   >> 4U) ^ (IData)(vlSelfRef.accumulator__DOT__c0)))));
    bufp->fullBit(oldp+18,((1U & ((IData)(vlSelfRef.S) 
                                  >> 5U))));
    bufp->fullBit(oldp+19,((1U & (((IData)(vlSelfRef.S) 
                                   >> 5U) ^ (((IData)(vlSelfRef.S) 
                                              >> 4U) 
                                             & (IData)(vlSelfRef.accumulator__DOT__c0))))));
    bufp->fullCData(oldp+20,((0x0000000fU & (IData)(vlSelfRef.S))),4);
    bufp->fullBit(oldp+21,((1U & (IData)(vlSelfRef.A))));
    bufp->fullBit(oldp+22,((1U & (IData)(vlSelfRef.S))));
    bufp->fullBit(oldp+23,((1U & ((IData)(vlSelfRef.A) 
                                  >> 1U))));
    bufp->fullBit(oldp+24,((1U & ((IData)(vlSelfRef.S) 
                                  >> 1U))));
    bufp->fullBit(oldp+25,((1U & ((IData)(vlSelfRef.A) 
                                  >> 2U))));
    bufp->fullBit(oldp+26,((1U & ((IData)(vlSelfRef.S) 
                                  >> 2U))));
    bufp->fullBit(oldp+27,((1U & ((IData)(vlSelfRef.A) 
                                  >> 3U))));
    bufp->fullBit(oldp+28,((1U & ((IData)(vlSelfRef.S) 
                                  >> 3U))));
}
