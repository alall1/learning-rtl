// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vaccumulator.h for the primary calling header

#include "Vaccumulator__pch.h"

bool Vaccumulator___024root___trigger_anySet__ico(const VlUnpacked<QData/*63:0*/, 2> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccumulator___024root___trigger_anySet__ico\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((2U > n));
    return (0U);
}

void Vaccumulator___024root___ico_sequent__TOP__0(Vaccumulator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccumulator___024root___ico_sequent__TOP__0\n"); );
    Vaccumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VdfgRegularize_hebeb780c_0_0 = (0x0000000fU 
                                                & ((IData)(vlSelfRef.A) 
                                                   ^ (IData)(vlSelfRef.S)));
    vlSelfRef.accumulator__DOT__ra__DOT__a1__DOT__Cin 
        = (1U & ((IData)(vlSelfRef.A) & (IData)(vlSelfRef.S)));
    vlSelfRef.accumulator__DOT__ra__DOT__a2__DOT__Cin 
        = (1U & ((((IData)(vlSelfRef.A) >> 1U) & ((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a1__DOT__Cin) 
                                                  | ((IData)(vlSelfRef.S) 
                                                     >> 1U))) 
                 | ((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a1__DOT__Cin) 
                    & ((IData)(vlSelfRef.S) >> 1U))));
    vlSelfRef.accumulator__DOT__ra__DOT__a3__DOT__Cin 
        = (1U & ((((IData)(vlSelfRef.A) >> 2U) & (((IData)(vlSelfRef.S) 
                                                   >> 2U) 
                                                  | (IData)(vlSelfRef.accumulator__DOT__ra__DOT__a2__DOT__Cin))) 
                 | ((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a2__DOT__Cin) 
                    & ((IData)(vlSelfRef.S) >> 2U))));
    vlSelfRef.accumulator__DOT__c0 = (1U & ((((IData)(vlSelfRef.A) 
                                              >> 3U) 
                                             & (((IData)(vlSelfRef.S) 
                                                 >> 3U) 
                                                | (IData)(vlSelfRef.accumulator__DOT__ra__DOT__a3__DOT__Cin))) 
                                            | ((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a3__DOT__Cin) 
                                               & ((IData)(vlSelfRef.S) 
                                                  >> 3U))));
    vlSelfRef.accumulator__DOT__sum = ((((4U & ((0x1ffffffcU 
                                                 & ((IData)(vlSelfRef.S) 
                                                    >> 3U)) 
                                                ^ (0x3ffffffcU 
                                                   & (((IData)(vlSelfRef.S) 
                                                       >> 2U) 
                                                      & ((IData)(vlSelfRef.accumulator__DOT__c0) 
                                                         << 2U))))) 
                                         | ((2U & (
                                                   (0x1ffffffeU 
                                                    & ((IData)(vlSelfRef.S) 
                                                       >> 3U)) 
                                                   ^ 
                                                   ((IData)(vlSelfRef.accumulator__DOT__c0) 
                                                    << 1U))) 
                                            | ((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a3__DOT__Cin) 
                                               ^ ((IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0) 
                                                  >> 3U)))) 
                                        << 3U) | ((4U 
                                                   & (((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a2__DOT__Cin) 
                                                       << 2U) 
                                                      ^ 
                                                      (0xfffffffcU 
                                                       & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)))) 
                                                  | ((2U 
                                                      & (((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a1__DOT__Cin) 
                                                          << 1U) 
                                                         ^ 
                                                         (0xfffffffeU 
                                                          & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)))) 
                                                     | (1U 
                                                        & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)))));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaccumulator___024root___dump_triggers__ico(const VlUnpacked<QData/*63:0*/, 2> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vaccumulator___024root___eval_phase__ico(Vaccumulator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccumulator___024root___eval_phase__ico\n"); );
    Vaccumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VicoExecute;
    // Body
    {
        // Inlined CFunc: _eval_triggers_vec__ico
        vlSelfRef.__VicoTriggered[0U] = (QData)((IData)(
                                                        ((((IData)(vlSelfRef.A) 
                                                           != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__A__0)) 
                                                          << 1U) 
                                                         | ((IData)(vlSelfRef.clk) 
                                                            != (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__0)))));
        vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
        vlSelfRef.__Vtrigprevexpr___TOP__A__0 = vlSelfRef.A;
        if (VL_UNLIKELY(((1U & (~ (IData)(vlSelfRef.__VicoDidInit)))))) {
            vlSelfRef.__VicoDidInit = 1U;
            vlSelfRef.__VicoTriggered[0U] = (1ULL | vlSelfRef.__VicoTriggered[0U]);
            vlSelfRef.__VicoTriggered[0U] = (2ULL | vlSelfRef.__VicoTriggered[0U]);
        }
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vaccumulator___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
    }
#endif
    __VicoExecute = Vaccumulator___024root___trigger_anySet__ico(vlSelfRef.__VicoTriggered);
    if (__VicoExecute) {
        {
            // Inlined CFunc: _eval_ico
            if ((2ULL & vlSelfRef.__VicoTriggered[0U])) {
                Vaccumulator___024root___ico_sequent__TOP__0(vlSelf);
                vlSelfRef.__Vm_traceActivity[1U] = 1U;
            }
        }
    }
    return (__VicoExecute);
}

bool Vaccumulator___024root___trigger_anySet__act(const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccumulator___024root___trigger_anySet__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        if (in[n]) {
            return (1U);
        }
        n = ((IData)(1U) + n);
    } while ((1U > n));
    return (0U);
}

void Vaccumulator___024root___trigger_orInto__act_vec_vec(VlUnpacked<QData/*63:0*/, 1> &out, const VlUnpacked<QData/*63:0*/, 1> &in) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccumulator___024root___trigger_orInto__act_vec_vec\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = (out[n] | in[n]);
        n = ((IData)(1U) + n);
    } while ((0U >= n));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vaccumulator___024root___dump_triggers__act(const VlUnpacked<QData/*63:0*/, 1> &triggers, const std::string &tag);
#endif  // VL_DEBUG

bool Vaccumulator___024root___eval_phase__act(Vaccumulator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccumulator___024root___eval_phase__act\n"); );
    Vaccumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    {
        // Inlined CFunc: _eval_triggers_vec__act
        vlSelfRef.__VactTriggered[0U] = (QData)((IData)(
                                                        ((IData)(vlSelfRef.clk) 
                                                         & (~ (IData)(vlSelfRef.__Vtrigprevexpr___TOP__clk__1)))));
        vlSelfRef.__Vtrigprevexpr___TOP__clk__1 = vlSelfRef.clk;
    }
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vaccumulator___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
    }
#endif
    Vaccumulator___024root___trigger_orInto__act_vec_vec(vlSelfRef.__VnbaTriggered, vlSelfRef.__VactTriggered);
    return (0U);
}

void Vaccumulator___024root___trigger_clear__act(VlUnpacked<QData/*63:0*/, 1> &out) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccumulator___024root___trigger_clear__act\n"); );
    // Locals
    IData/*31:0*/ n;
    // Body
    n = 0U;
    do {
        out[n] = 0ULL;
        n = ((IData)(1U) + n);
    } while ((1U > n));
}

bool Vaccumulator___024root___eval_phase__nba(Vaccumulator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccumulator___024root___eval_phase__nba\n"); );
    Vaccumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = Vaccumulator___024root___trigger_anySet__act(vlSelfRef.__VnbaTriggered);
    if (__VnbaExecute) {
        {
            // Inlined CFunc: _eval_nba
            if ((1ULL & vlSelfRef.__VnbaTriggered[0U])) {
                {
                    // Inlined CFunc: _nba_sequent__TOP__0
                    vlSelfRef.overflow = ((IData)(vlSelfRef.overflow) 
                                          | ((IData)(vlSelfRef.accumulator__DOT__c0) 
                                             & (0x30U 
                                                == 
                                                (0x30U 
                                                 & (IData)(vlSelfRef.S)))));
                    vlSelfRef.S = vlSelfRef.accumulator__DOT__sum;
                    vlSelfRef.__VdfgRegularize_hebeb780c_0_0 
                        = (0x0000000fU & ((IData)(vlSelfRef.A) 
                                          ^ (IData)(vlSelfRef.S)));
                    vlSelfRef.accumulator__DOT__ra__DOT__a1__DOT__Cin 
                        = (1U & ((IData)(vlSelfRef.A) 
                                 & (IData)(vlSelfRef.S)));
                    vlSelfRef.accumulator__DOT__ra__DOT__a2__DOT__Cin 
                        = (1U & ((((IData)(vlSelfRef.A) 
                                   >> 1U) & ((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a1__DOT__Cin) 
                                             | ((IData)(vlSelfRef.S) 
                                                >> 1U))) 
                                 | ((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a1__DOT__Cin) 
                                    & ((IData)(vlSelfRef.S) 
                                       >> 1U))));
                    vlSelfRef.accumulator__DOT__ra__DOT__a3__DOT__Cin 
                        = (1U & ((((IData)(vlSelfRef.A) 
                                   >> 2U) & (((IData)(vlSelfRef.S) 
                                              >> 2U) 
                                             | (IData)(vlSelfRef.accumulator__DOT__ra__DOT__a2__DOT__Cin))) 
                                 | ((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a2__DOT__Cin) 
                                    & ((IData)(vlSelfRef.S) 
                                       >> 2U))));
                    vlSelfRef.accumulator__DOT__c0 
                        = (1U & ((((IData)(vlSelfRef.A) 
                                   >> 3U) & (((IData)(vlSelfRef.S) 
                                              >> 3U) 
                                             | (IData)(vlSelfRef.accumulator__DOT__ra__DOT__a3__DOT__Cin))) 
                                 | ((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a3__DOT__Cin) 
                                    & ((IData)(vlSelfRef.S) 
                                       >> 3U))));
                    vlSelfRef.accumulator__DOT__sum 
                        = ((((4U & ((0x1ffffffcU & 
                                     ((IData)(vlSelfRef.S) 
                                      >> 3U)) ^ (0x3ffffffcU 
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
                                      >> 3U)))) << 3U) 
                           | ((4U & (((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a2__DOT__Cin) 
                                      << 2U) ^ (0xfffffffcU 
                                                & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)))) 
                              | ((2U & (((IData)(vlSelfRef.accumulator__DOT__ra__DOT__a1__DOT__Cin) 
                                         << 1U) ^ (0xfffffffeU 
                                                   & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)))) 
                                 | (1U & (IData)(vlSelfRef.__VdfgRegularize_hebeb780c_0_0)))));
                }
                vlSelfRef.__Vm_traceActivity[2U] = 1U;
            }
        }
        Vaccumulator___024root___trigger_clear__act(vlSelfRef.__VnbaTriggered);
    }
    return (__VnbaExecute);
}

void Vaccumulator___024root___eval(Vaccumulator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccumulator___024root___eval\n"); );
    Vaccumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Locals
    IData/*31:0*/ __VicoIterCount;
    IData/*31:0*/ __VnbaIterCount;
    // Body
    __VicoIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vaccumulator___024root___dump_triggers__ico(vlSelfRef.__VicoTriggered, "ico"s);
#endif
            VL_FATAL_MT("accumulator.sv", 1, "", "DIDNOTCONVERGE: Input combinational region did not converge after '--converge-limit' of 10000 tries");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        vlSelfRef.__VicoPhaseResult = Vaccumulator___024root___eval_phase__ico(vlSelf);
    } while (vlSelfRef.__VicoPhaseResult);
    __VnbaIterCount = 0U;
    do {
        if (VL_UNLIKELY(((0x00002710U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vaccumulator___024root___dump_triggers__act(vlSelfRef.__VnbaTriggered, "nba"s);
#endif
            VL_FATAL_MT("accumulator.sv", 1, "", "DIDNOTCONVERGE: NBA region did not converge after '--converge-limit' of 10000 tries");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        vlSelfRef.__VactIterCount = 0U;
        do {
            if (VL_UNLIKELY(((0x00002710U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vaccumulator___024root___dump_triggers__act(vlSelfRef.__VactTriggered, "act"s);
#endif
                VL_FATAL_MT("accumulator.sv", 1, "", "DIDNOTCONVERGE: Active region did not converge after '--converge-limit' of 10000 tries");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactPhaseResult = Vaccumulator___024root___eval_phase__act(vlSelf);
        } while (vlSelfRef.__VactPhaseResult);
        vlSelfRef.__VnbaPhaseResult = Vaccumulator___024root___eval_phase__nba(vlSelf);
    } while (vlSelfRef.__VnbaPhaseResult);
}

#ifdef VL_DEBUG
void Vaccumulator___024root___eval_debug_assertions(Vaccumulator___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vaccumulator___024root___eval_debug_assertions\n"); );
    Vaccumulator__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");
    }
    if (VL_UNLIKELY(((vlSelfRef.A & 0xf0U)))) {
        Verilated::overWidthError("A");
    }
}
#endif  // VL_DEBUG
