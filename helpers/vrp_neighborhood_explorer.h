#ifndef _VRP_NEIGHBORHOOD_EXPLORER_H_
#define _VRP_NEIGHBORHOOD_EXPLORER_H_
#include <helpers/NeighborhoodExplorer.hh>
#include <vector>
#include <string>
#include <utility>
#include "data/neighbor.h"
#include "data/route.h"
#include "data/prob_input.h"
#include "helpers/vrp_state_manager.h"

// #define _VRP_DEBUG_

template <class Move>
class TabuNeighborhoodExplorer:
public NeighborhoodExplorer<ProbInput, RoutePlan, Move> {
 public:
    virtual void RandomMove(const RoutePlan&, Move&) const = 0;
    virtual void FirstMove(const RoutePlan&, Move&) const = 0;
    virtual bool NextMove(const RoutePlan&, Move&) const = 0;
    virtual void MakeMove(RoutePlan&, const Move&) const = 0;
 protected:
    TabuNeighborhoodExplorer(const ProbInput &in,
                             VRPStateManager &sm, std::string nm):
        NeighborhoodExplorer<ProbInput, RoutePlan, Move>(in, sm, nm) { }
    void UpdateRouteTimetable(std::vector<int>&, const Route&) const;
    int RouteCostsOnTimeWindow(const Route&, const std::vector<int>&, int*) const;
    mutable std::vector<Route> routes_;
    mutable std::vector<std::vector<int> > timetable_;
    mutable int delta_num_order_late_return;
};

class InsMoveNeighborhoodExplorer: public TabuNeighborhoodExplorer<InsMove> {
 public:
    InsMoveNeighborhoodExplorer(const ProbInput &in, VRPStateManager &sm):
        TabuNeighborhoodExplorer<InsMove>(in, sm, "InsMoveNeighborhood") { }

    // move generation
    void RandomMove(const RoutePlan&, InsMove&) const;
    void FirstMove(const RoutePlan&, InsMove&) const;
    bool NextMove(const RoutePlan&, InsMove&) const;
    bool FeasibleMove(const RoutePlan&, const InsMove&) const;
    void MakeMove(RoutePlan&, const InsMove&) const;

    // delta cost
    int DeltaCostFunction(const RoutePlan&, const InsMove&) const;
    int DeltaObjective(const RoutePlan&, const InsMove &) const;
    int DeltaViolations(const RoutePlan&, const InsMove &) const;

 private:
    void AnyRandomMove(const RoutePlan&, InsMove&) const;
    bool AnyNextMove(const RoutePlan&, InsMove&) const;
    int DeltaDateViolationCost(const RoutePlan&,
                                    const InsMove&, int) const;     // s1
    int DeltaTimeViolationCost(const RoutePlan&,
                                    const InsMove&, int) const;     // s2
    int DeltaOptOrderCost(const RoutePlan&,
                               const InsMove&, int) const;          // s3
    int DeltaTranportationCost(const RoutePlan&, const InsMove&) const;
                                                                    // s4
    int DeltaCapExceededCost(const RoutePlan&,
                                  const InsMove&, int) const;       // h1
    int DeltaLateReturnCost(const RoutePlan&, const InsMove&, int) const;
                                                                    // h2
    // RoutePlan old_state;
};

class InterSwapNeighborhoodExplorer:
public TabuNeighborhoodExplorer<InterSwap> {
 public:
    InterSwapNeighborhoodExplorer(const ProbInput &in, VRPStateManager &sm):
        TabuNeighborhoodExplorer<InterSwap>(in, sm, "InterSwapNeighborhood") { }

    // move generation
    void RandomMove(const RoutePlan&, InterSwap&) const;
    void FirstMove(const RoutePlan&, InterSwap&) const;
    bool NextMove(const RoutePlan&, InterSwap&) const;
    bool FeasibleMove(const RoutePlan&, const InterSwap&) const;
    void MakeMove(RoutePlan&, const InterSwap&) const;

    // delta cost
    int DeltaCostFunction(const RoutePlan&, const InterSwap&) const;
    int DeltaObjective(const RoutePlan&, const InterSwap &) const;
    int DeltaViolations(const RoutePlan&, const InterSwap &) const;

 private:
    void AnyRandomMove(const RoutePlan&, InterSwap&) const;
    bool AnyNextMove(const RoutePlan&, InterSwap&) const;
    int DeltaDateViolationCost(const RoutePlan&,
                                    const InterSwap&, int) const;   // s1
    int DeltaTimeViolationCost(const RoutePlan&,
                                    const InterSwap&, int) const;    // s2
    int DeltaOptOrderCost(const RoutePlan&,
                                    const InterSwap&, int) const;   // s3
    int DeltaTranportationCost(const RoutePlan&, const InterSwap&) const;
                                                                    // s4
    int DeltaCapExceededCost(const RoutePlan&,
                                  const InterSwap&, int) const;     // h1
    int DeltaLateReturnCost(const RoutePlan&, const InterSwap&, int) const;
                                                                    // h2
};

class IntraSwapNeighborhoodExplorer:
public TabuNeighborhoodExplorer<IntraSwap> {
 public:
    IntraSwapNeighborhoodExplorer(const ProbInput &in, VRPStateManager &sm):
        TabuNeighborhoodExplorer<IntraSwap>(in, sm, "IntraSwapNeighborhood") { }

    // move generation
    void RandomMove(const RoutePlan&, IntraSwap&) const;
    void FirstMove(const RoutePlan&, IntraSwap&) const;
    bool NextMove(const RoutePlan&, IntraSwap&) const;
    bool FeasibleMove(const RoutePlan&, const IntraSwap&) const;
    void MakeMove(RoutePlan&, const IntraSwap&) const;

    // delta cost
    int DeltaCostFunction(const RoutePlan&, const IntraSwap&) const;
    int DeltaObjective(const RoutePlan&, const IntraSwap &) const;
    int DeltaViolations(const RoutePlan&, const IntraSwap &) const;

 private:
    void AnyRandomMove(const RoutePlan&, IntraSwap&) const;
    bool AnyNextMove(const RoutePlan&, IntraSwap&) const;
    int DeltaDateViolationCost(const RoutePlan&,
                                    const IntraSwap&, int) const;    // s1
    int DeltaTimeViolationCost(const RoutePlan&,
                                    const IntraSwap&, int) const;    // s2
    int DeltaOptOrderCost(const RoutePlan&,
                               const IntraSwap&, int) const;         // s3
    int DeltaTranportationCost(const RoutePlan&, const IntraSwap&) const;
                                                                     // s4
    int DeltaCapExceededCost(const RoutePlan&,
                                  const IntraSwap&, int) const;      // h1
    int DeltaLateReturnCost(const RoutePlan&, const IntraSwap&, int) const;
                                                                     // h2
};

// Implementation

template <class Move>
void
TabuNeighborhoodExplorer<Move>::UpdateRouteTimetable(std::vector<int> &ret,
                                                     const Route &r) const {
    int arrive_time = this->in.get_depart_time();
    int stop_time = this->in.get_depart_time();
    std::string client_from(this->in.get_depot());
    unsigned route_size = r.size();
    ret.clear();
    for (unsigned i = 0; i <= route_size; ++i) {
        std::string client_to(this->in.get_depot());
        if (i < route_size)
            client_to = this->in.OrderGroupVect(r[i]).get_client();
        if (client_from != client_to) {
            int ready_time = this->in.FindClient(client_to).get_ready_time();
            arrive_time += this->in.FindClient(client_from).get_service_time()
                            + this->in.get_time_dist(client_from, client_to);

            if (arrive_time - stop_time > 45 * 360) {    // driving rests
                arrive_time += 45 * 60;
                if (arrive_time < ready_time)
                    arrive_time = ready_time;
                stop_time = arrive_time;
            } else if (arrive_time < ready_time) {
                if (ready_time - arrive_time >= 45 * 60)
                    stop_time = ready_time;
                arrive_time = ready_time;
            }
        }
        ret.push_back(arrive_time);
        client_from = client_to;
    }
    return;
}

template <class Move> int
TabuNeighborhoodExplorer<Move>::RouteCostsOnTimeWindow(const Route &r,
                                                       const std::vector<int> &time,
                                                       int *late_return) const {
    bool over_time = false;
    int cost = 0, day = -1, final_day = 86399;
    int prev_arrive_time = this->in.get_depart_time();
    for (unsigned i = 0; i <= r.size(); ++i) {
        int og_size = 1, duetime = this->in.get_return_time();
        if (i < r.size()) {
            const OrderGroup &og = this->in.OrderGroupVect(r[i]);
            duetime = this->in.FindClient(og.get_client()).get_due_time();
            og_size = og.size();
        }
        int tt = time[i];  // get arrive time of order j on route i
        if (tt < prev_arrive_time) {
            over_time = true;
            day++;
        }
        if (tt > duetime || over_time) {
            if (over_time) {    // arrive time past current day
                tt += final_day - duetime + day * 86400;
                cost += tt * og_size;
                if (i == r.size())
                    *late_return += r.size();
            } else {
                cost += (tt - duetime) * og_size;
                // later 1 hour
                if (i == r.size() && tt - duetime > 3600)
                    *late_return += r.size();
            }
        }
        prev_arrive_time = tt;
    }
    return cost;
    // for (unsigned i = pos; i < r.size(); ++i) {
    //     std::string client = this->in.OrderGroupVect(r[i]).get_client();
    //     int duetime = this->in.FindClient(client).get_due_time();
    //     int arrive_time = rp(r, i);
    //     if (arrive_time > duetime)
    //         delta -= arrive_time - duetime;
    // }

    // // after move
    // for (unsigned i = pos; i < routes_[isnew].size(); ++i) {
    //     const OrderGroup &og = in.OrderGroupVect(routes_[isnew][i]);
    //     int duetime = this->in.FindClient(og.get_client()).get_due_time();
    //     if (timetable_[isnew][i] > duetime)
    //         delta += timetable_[isnew][i] - duetime;
    // }
    // return delta;
}

#endif
