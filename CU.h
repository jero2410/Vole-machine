class CU {


public:
    void load(int idxReg, int idxMem, Register& r, Memory& m) {
        try {
            r.setCell(idxReg, m.getCell(idxMem));
        } catch (const out_of_range& e) {
            throw runtime_error("Invalid address in LOAD operation");
        }
    }

    void load(int idxReg, int val, Register& r) {
        try {
            r.setCell(idxReg, val);
        } catch (const out_of_range& e) {
            throw runtime_error("Invalid register in LOAD operation");
        }
    }

    void store(int idxReg, int idxMem, Register& r, Memory& m) {
        try {
            m.setCell(idxMem, r.getCell(idxReg));
        } catch (const out_of_range& e) {
            throw runtime_error("Invalid address in STORE operation");
        }
    }

    void move(int idxReg1, int idxReg2, Register& r) {
        try {
            r.setCell(idxReg1, r.getCell(idxReg2));
        } catch (const out_of_range& e) {
            throw runtime_error("Invalid register in MOVE operation");
        }
    }

    void jump(int idxReg, int idxMem, Register& r, int& PC) {
        try {
            if (r.getCell(idxReg) == r.getCell(0)) {
                PC = idxMem;
            }
        } catch (const out_of_range& e) {
            throw runtime_error("Invalid address in JUMP operation");
        }
    }
    void jump2(int idxReg, int idxMem, Register& r, int& PC) {
        try {
            if (r.getCell(idxReg) > r.getCell(0)) {
                PC = idxMem;
            }
        } catch (const out_of_range& e) {
            throw runtime_error("Invalid address in JUMP operation");
        }
    }

    void halt() {
        throw runtime_error("HALT");
    }
};
