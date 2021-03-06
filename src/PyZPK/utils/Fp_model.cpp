#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>
#include <pybind11/cast.h>
#include <pybind11/complex.h>
#include <vector>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <limits>
#include <random>
#include <cstddef>
#include <iostream>
#include <libff/algebra/scalar_multiplication/multiexp.hpp>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pp.hpp>
#include <libff/algebra/curves/mnt/mnt6/mnt6_g1.hpp>
#include <libff/algebra/curves/mnt/mnt6/mnt6_g2.hpp>
#include <libff/algebra/curves/mnt/mnt6/mnt6_init.hpp>
#include <libff/algebra/curves/mnt/mnt6/mnt6_pairing.hpp>
#include <libff/algebra/curves/public_params.hpp>
#include <libff/algebra/exponentiation/exponentiation.hpp>
#include <libff/algebra/fields/field_utils.hpp>
#include <libff/algebra/fields/bigint.hpp>
#include <libff/algebra/fields/fp_aux.tcc>
#include <libff/common/profiling.hpp>
#include <libff/common/utils.hpp>
#include <libff/common/serialization.hpp>
#include <gmp.h>

using namespace std;
namespace py = pybind11;
using namespace libff;

// Used as FieldT class type
void init_utils_Fp_model(py::module &m)
{
    // bigint wrapper class around GMP's MPZ long integers.
    py::class_<bigint<5l>>(m, "bigint")
        .def(py::init<>())
        .def(py::init<const unsigned long>())
        .def(py::init<const char*>())
        .def("test_bit", &bigint<5l>::test_bit)
        .def("randomize", &bigint<5l>::randomize);

    py::class_<mnt6_pp>(m, "mnt6_pp");

    //  Implementation of arithmetic in the finite field F[p], for prime p of fixed length.
    py::class_<Fp_model<5l, libff::mnt46_modulus_B>>(m, "Fp_model")
        .def(py::init<>())
        .def(py::init<const bigint<5l> &>())
        .def(py::init<const long, const bool>())
        .def_readwrite("mont_repr", &Fp_model<5l, libff::mnt46_modulus_B>::mont_repr)
        .def("random_element", &Fp_model<5l, libff::mnt46_modulus_B>::random_element) // Todo
        .def("inverse", &Fp_model<5l, libff::mnt46_modulus_B>::inverse);
        
}