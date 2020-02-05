// copyright defined in LICENSE.txt

#pragma once
#include "action_callbacks.hpp"
#include "state_history_rocksdb.hpp"
#include "wasm_ql_plugin.hpp"

#include <eosio/vm/backend.hpp>

namespace wasm_ql {

struct shared_state {
    bool                                console      = {};
    std::string                         allow_origin = {};
    std::string                         contract_dir = {};
    std::string                         static_dir   = {};
    std::shared_ptr<chain_kv::database> db;

    shared_state(std::shared_ptr<chain_kv::database> db)
        : db(std::move(db)) {}
};

struct thread_state : history_tools::action_state {
    std::shared_ptr<const shared_state> shared = {};
    eosio::vm::wasm_allocator           wa     = {};
};

void register_callbacks();

const std::vector<char>& query_get_info(wasm_ql::thread_state& thread_state);
const std::vector<char>& query_get_block(wasm_ql::thread_state& thread_state, std::string_view body);
const std::vector<char>& query_send_transaction(wasm_ql::thread_state& thread_state, std::string_view body);

} // namespace wasm_ql
