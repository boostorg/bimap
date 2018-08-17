// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  VC++ 8.0 warns on usage of certain Standard Library and API functions that
//  can be cause buffer overruns or other possible security issues if misused.
//  See http://msdn.microsoft.com/msdnmag/issues/05/05/SafeCandC/default.aspx
//  But the wording of the warning is misleading and unsettling, there are no
//  portable alternative functions, and VC++ 8.0's own libraries use the
//  functions in question. So turn off the warnings.
#define _CRT_SECURE_NO_DEPRECATE
#define _SCL_SECURE_NO_DEPRECATE

#include <boost/config.hpp>
#include <boost/type_traits/is_convertible.hpp>

// std
#include <set>
#include <map>
#include <cstddef>
#include <cassert>
#include <algorithm>

// Boost.Test
#include <boost/core/lightweight_test.hpp>
#include <boost/core/lightweight_test_trait.hpp>

// Boost.Bimap

#include <boost/bimap/set_of.hpp>
#include <boost/bimap/property_map/set_support.hpp>

#include <boost/bimap/unordered_set_of.hpp>
#include <boost/bimap/property_map/unordered_set_support.hpp>

#include <boost/bimap/bimap.hpp>

template <typename Map>
void
    test_readable_property_map(
        Map m
      , BOOST_DEDUCED_TYPENAME boost::property_traits<
            Map
        >::key_type const& key
      , BOOST_DEDUCED_TYPENAME boost::property_traits<
            Map
        >::value_type const& value
    )
{
    BOOST_TEST_TRAIT_TRUE((
        boost::is_convertible<
            BOOST_DEDUCED_TYPENAME boost::property_traits<Map>::category
          , boost::readable_property_map_tag
        >
    ));

    BOOST_TEST(get(m, key) == value);
#if 0
    BOOST_TEST(m[key] == value);
#endif
}

void test_bimap_property_map()
{
    using namespace boost::bimaps;

    typedef bimap<set_of<int>,unordered_set_of<double> > bm;

    bm b;
    b.insert(bm::value_type(1, 0.1));
    b.insert(bm::value_type(2, 0.2));
    b.insert(bm::value_type(3, 0.3));

    test_readable_property_map(b.left, 1, 0.1);
    test_readable_property_map(b.right, 0.1, 1);
}

int main(int, char*[])
{
    test_bimap_property_map();
    return boost::report_errors();
}

