hbar = 1.055e-34
m_0 = 9.1e-31
m = 0.0067 * m_0
eV = 1.6e-19
dl = 0.1e-9


def generate_network_block(num_rows, num_cols):
    content = ". title electron waveguide\n"
    zz_counter = 0
    for i in range(num_rows):
        for j in range(num_cols):
            this_num = i * num_cols + j
            left_num = i * num_cols + j - 1
            up_num = (i - 1) * num_cols + j
            if j - 1 < 0:
                content += "ZZ%d CENTER%d LEFT%d COMPLEX 0 %E\n" % (zz_counter, this_num, this_num, -m/hbar*dl)
            else:
                content += "ZZ%d CENTER%d RIGHT%d COMPLEX 0 %E\n" % (zz_counter, this_num, left_num, -m/hbar*dl)
            zz_counter += 1
            content += "ZZ%d RIGHT%d CENTER%d COMPLEX 0 %E\n" % (zz_counter, this_num, this_num, -m/hbar*dl)
            zz_counter += 1
            if i - 1 < 0:
                content += "ZZ%d CENTER%d UP%d COMPLEX 0 %E\n" % (zz_counter, this_num, this_num, -m/hbar*dl)
            else:
                content += "ZZ%d CENTER%d DOWN%d COMPLEX 0 %E\n" % (zz_counter, this_num, up_num, -m/hbar*dl)
            zz_counter += 1
            content += "ZZ%d DOWN%d CENTER%d COMPLEX 0 %E\n" % (zz_counter, this_num, this_num, -m/hbar*dl)
            content += "C%d CENTER%d 0 %E\n" % (this_num, this_num, dl)
            zz_counter += 1

    content += "V1 LEFT%d 0 DC 0 AC 1\n" % (int(num_rows / 2) * num_cols)
    content += ".CONTROL\n"
    content += "AC LIN 10000 0.24E14 2.4E14\n"
    content += "PLOT RIGHT%d\n" % (int(num_rows / 2) * num_cols + num_cols - 1)
    content += ".ENDC"
    content += ".END"
    return content


context = generate_network_block(100, 1000)
f = open("electron_waveguide.cir", "w")
f.write(context)
f.close()
