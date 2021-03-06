import pytest
import pyzpk
import math

# Test for QAP
@pytest.mark.parametrize("qap_degree, num_inputs, binary_input",
                         [
                             # basic_domain_size
                             (1 << pyzpk.mnt6_Fr_s, 10, True),
                             # step_domain_size
                             ((1 << 10) + (1 << 8), 10, True),
                             # extended_domain_size
                             (1 << (pyzpk.mnt6_Fr_s+1), 10, True),
                             # extended_domain_size_special
                             ((1 << (pyzpk.mnt6_Fr_s+1))-1, 10, True)
                         ])
def test_qap(qap_degree, num_inputs, binary_input):
    assert num_inputs + 1 <= qap_degree
    num_constraints = qap_degree - num_inputs - 1
    # For Binary input
    example = pyzpk.generate_r1cs_example_with_binary_input(
        num_constraints, num_inputs)
    assert example.constraint_system.is_satisfied(
        example.primary_input, example.auxiliary_input)

# Test for SAP
@pytest.mark.parametrize("sap_degree, num_inputs, binary_input",
                         [
                             # basic_domain_size_special
                             ((1 << pyzpk.mnt6_Fr_s) - 1, 10, True),
                             #  # step_domain_size_special
                             ((1 << 10) + (1 << 8) - 1, 10, True),
                             #  # extended_domain_size_special
                             (1 << (pyzpk.mnt6_Fr_s+1) - 1, 10, True)
                         ])
def test_sap(sap_degree, num_inputs, binary_input):
    num_constraints = int((sap_degree - 1) / 2) - num_inputs
    assert num_constraints >= 1
    # For Binary input
    example = pyzpk.generate_r1cs_example_with_binary_input(
        num_constraints, num_inputs)
    assert example.constraint_system.is_satisfied(
        example.primary_input, example.auxiliary_input)
