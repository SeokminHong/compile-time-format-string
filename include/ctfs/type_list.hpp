#ifndef CTFS_TYPE_LIST_HPP
#define CTFS_TYPE_LIST_HPP

namespace ctfs {
template <typename... Type> struct type_list { using type = type_list; };
} // namespace ctfs

#endif // CTFS_TYPE_LIST_HPP