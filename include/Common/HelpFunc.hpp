#ifndef HELPFUNC_HPP
#define HELPFUNC_HPP

#define SET_STATE(var, state) (var = state)
#define ATTACH_STATE(var, state, type) (var = static_cast<type>(var|state))
#define HAS_STATE(var, state) (var&state)
#define UNSET_STATE(var, state, type) (var = static_cast<type>(var&(~state)))
#define IS_STATE(var, state) (var==state)

#endif
