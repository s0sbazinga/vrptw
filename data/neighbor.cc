#include "data/neighbor.h"

std::ostream& operator<<(std::ostream &os, const InsMove &mv) {
    os << "order: " << mv.order << ", " << "old: (" << mv.old_route
       << ", " << mv.old_pos << "), " << "new: (" << mv.new_route
       << ", " << mv.new_pos << ")";
    return os;
}

bool InsMove::operator==(const InsMove &m) const {
    return (order == m.order) && (old_route == m.old_route)
           && (old_pos == m.old_pos) && (new_route == m.new_route)
           && (new_pos == m.new_pos);
}

bool InsMove::operator!=(const InsMove &m) const {
    return !(operator==(m));
}

std::ostream& operator<<(std::ostream &os, const InterSwap &mv) {
    os << "(" << mv.ord1 << ", " << mv.ord2 << ", "
       << mv.route1 << ", " << mv.pos1 << ", " << mv.route2
       << ", " << mv.pos2 << ")";
    return os;
}

bool InterSwap::operator==(const InterSwap &m) const {
    return (ord1 == m.ord1) && (ord2 == m.ord2)
           && (route1 == m.route1) && (route2 == m.route2)
           && (pos1 == m.pos1) && (pos2 == m.pos2);
}

bool InterSwap::operator!=(const InterSwap &m) const {
    return !(operator==(m));
}

std::ostream& operator<<(std::ostream &os, const IntraSwap &mv) {
    os << "(" << mv.ord1 << ", " << mv.ord2 << ", "
       << mv.route << ", " << mv.pos1 << ", " << mv.pos2
       << ")";
    return os;
}

bool IntraSwap::operator==(const IntraSwap &m) const {
    return (ord1== m.ord1) && (ord2 == m.ord2)
           && (pos1 == m.pos1) && (pos2 == m.pos2);
}

bool IntraSwap::operator!=(const IntraSwap &m) const {
    return !(operator==(m));
}
