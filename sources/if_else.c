If : tIF tPARENT_OPEN Condition tPARENT_CLOSE BlocOp
            {
                $$ = label_get_next_tmp_label();
                instr_emit_jmp($$);
                instr_emit_label($3);
            }
Else : tELSE BlocOp

IfElse : If
            {
                instr_emit_label($1);
            }
       | If Else
            {
                instr_emit_label($1);
            }
       ;

ComparaisonOperator : tEQUAL_BOOLEAN
            {
                $$ = instr_emit_equ_rel_reg;
            }
            | tSMALLER
            {
                $$ = instr_emit_inf_rel_reg;
            }
            | tGREATER
            {
                $$ = instr_emit_sup_rel_reg;
            }
            ;

Condition : ExprArith ComparaisonOperator ExprArith
            {
                int tmp;

                symfun_current_pop();
                symfun_current_pop();

                tmp = symfun_current_add_symbol_temp();
                symfun_current_pop();

                ($2)(BP_REG, tmp, $1, $3);

                $$ = label_get_next_tmp_label();
                instr_emit_jmf_rel_reg(BP_REG, tmp, $$);

            }
            | ExprArith ComparaisonOperator tEQUAL ExprArith
            {
                int tmp;
                int label_equal, label_equal_end;

                tmp = symfun_current_add_symbol_temp();
                ($2)(BP_REG, tmp, $1, $4);

                $$ = label_get_next_tmp_label();
                label_equal_end = label_get_next_tmp_label();
                label_equal = label_get_next_tmp_label();
                instr_emit_jmf_rel_reg(BP_REG, tmp, label_equal);
                instr_emit_jmp(label_equal_end);

                instr_emit_label(label_equal);
                instr_emit_equ_rel_reg(BP_REG, tmp, $1, $4);
                instr_emit_jmf_rel_reg(BP_REG, tmp, $$);
                instr_emit_label(label_equal_end);

                symfun_current_pop();
                symfun_current_pop();
                symfun_current_pop();
            }
            | ExprArith tDIFFERENT ExprArith
            {
                int tmp_const = 0;
                int tmp_res = 0;

                symfun_current_pop();
                symfun_current_pop();

                tmp_res = symfun_current_add_symbol_temp();
                instr_emit_equ(tmp_res, $1, $3);

                tmp_const = symfun_current_add_symbol_temp();

                instr_emit_afc_rel_reg(BP_REG, tmp_const, 1);

                instr_emit_sou_rel_reg(BP_REG, tmp_res, tmp_res, tmp_const);
                symfun_current_pop();
                symfun_current_pop();

                $$ = label_get_next_tmp_label();
                instr_emit_jmf_rel_reg(BP_REG, tmp_res, $$);
            }
            ;