RegOffset : tBRACKET_OPEN Reg tPLUS tNUMBER tBRACKET_CLOSE { 
        struct reg_offset ret = {$2, $4};
        $$ = ret;
    };
Reg : tID { $$ = instr_reg_to_int($1); }
Label : tID { $$ = label_table_hash_string($1); }
DeclareLabel : tID tLABEL_END { $$ = label_add($1); instr_emit_label($$); }
Address : tBRACKET_OPEN tDOLLAR tNUMBER tBRACKET_CLOSE { $$ = $3; }

Cop : tCOP Address tCOMA Address { instr_emit_cop($2, $4); }
    | tCOP Reg tCOMA Reg { instr_emit_cop_reg($2, $4); }
    | tCOP RegOffset tCOMA RegOffset { instr_emit_cop_rel_reg($2.reg, $2.off, $4.reg, $4.off); }