#ifndef CEPH_RGW_ADMIN_MULTISITE_H
#define CEPH_RGW_ADMIN_MULTISITE_H

#include <boost/optional.hpp>
#include "rgw_sync.h"
#include "rgw_data_sync.h"
#include "rgw_admin_common.h"

// This header and the corresponding source file contain handling of the following commads / groups of commands:
// Period, realm, zone, zonegroup, data sync, metadata sync

/// search each zonegroup for a connection
boost::optional<RGWRESTConn> get_remote_conn(RGWRados *store, const RGWPeriodMap& period_map,
                                             const std::string& remote);

int send_to_url(const std::string& url, const std::string& access, const std::string& secret, req_info& info, bufferlist& in_data,
                JSONParser& parser);

int send_to_remote_or_url(RGWRESTConn *conn, const std::string& url, const std::string& access, const std::string& secret,
                          req_info& info, bufferlist& in_data, JSONParser& parser);

int commit_period(RGWRados *store, RGWRealm& realm, RGWPeriod& period, std::string remote, const std::string& url,
                  const std::string& access, const std::string& secret, bool force);

int update_period(RGWRados *store, const std::string& realm_id, const std::string& realm_name, const std::string& period_id,
                  const std::string& period_epoch, bool commit, const std::string& remote, const std::string& url,
                  const std::string& access, const std::string& secret, Formatter *formatter, bool force);

int do_period_pull(RGWRados *store, RGWRESTConn *remote_conn, const std::string& url,
                   const std::string& access_key, const std::string& secret_key,
                   const std::string& realm_id, const std::string& realm_name,
                   const std::string& period_id, const std::string& period_epoch,
                   RGWPeriod *period);

int handle_opt_period_delete(const std::string& period_id, CephContext *context, RGWRados *store);

int handle_opt_period_get(const std::string& period_epoch, std::string& period_id, bool staging, std::string& realm_id,
                          std::string& realm_name, CephContext *context, RGWRados *store, Formatter *formatter);

int handle_opt_period_get_current(const std::string& realm_id, const std::string& realm_name, RGWRados *store, Formatter *formatter);

int handle_opt_period_list(RGWRados *store, Formatter *formatter);

int handle_opt_period_pull(const std::string& period_id, const std::string& period_epoch, const std::string& realm_id,
                           const std::string& realm_name, const std::string& url, const std::string& access_key, const std::string& secret_key,
                           std::string& remote, CephContext *context, RGWRados *store, Formatter *formatter);

int handle_opt_period_push(const std::string& period_id, const std::string& period_epoch, const std::string& realm_id,
                           const std::string& realm_name, const std::string& url, const std::string& access_key, const std::string& secret_key,
                           CephContext *context, RGWRados *store);

int handle_opt_period_commit(const std::string& period_id, const std::string& period_epoch, const std::string& realm_id,
                             const std::string& realm_name, const std::string& url, const std::string& access_key,
                             const std::string& secret_key, const std::string& remote, bool yes_i_really_mean_it,
                             CephContext *context, RGWRados *store, Formatter *formatter);

int handle_opt_realm_create(const std::string& realm_name, bool set_default, CephContext *context, RGWRados *store,
                            Formatter *formatter);

int handle_opt_realm_delete(const std::string& realm_id, const std::string& realm_name, CephContext *context, RGWRados *store);

int handle_opt_realm_get(const std::string& realm_id, const std::string& realm_name, CephContext *context, RGWRados *store,
                         Formatter *formatter);

int handle_opt_realm_get_default(CephContext *context, RGWRados *store);

int handle_opt_realm_list(CephContext *context, RGWRados *store, Formatter *formatter);

int handle_opt_realm_list_periods(const std::string& realm_id, const std::string& realm_name, RGWRados *store, Formatter *formatter);

int handle_opt_realm_rename(const std::string& realm_id, const std::string& realm_name, const std::string& realm_new_name,
                            CephContext *context, RGWRados *store);

int handle_opt_realm_set(const std::string& realm_id, const std::string& realm_name, const std::string& infile,
                         bool set_default, CephContext *context, RGWRados *store, Formatter *formatter);

int handle_opt_realm_default(const std::string& realm_id, const std::string& realm_name, CephContext *context, RGWRados *store);

int handle_opt_realm_pull(const std::string& realm_id, const std::string& realm_name, const std::string& url, const std::string& access_key,
                          const std::string& secret_key, bool set_default, CephContext *context, RGWRados *store,
                          Formatter *formatter);

int handle_opt_zonegroup_add(const std::string& zonegroup_id, const std::string& zonegroup_name, const std::string& zone_id,
                             const std::string& zone_name, bool tier_type_specified, std::string *tier_type,
                             const map<std::string, std::string, ltstr_nocase>& tier_config_add, bool sync_from_all_specified,
                             bool *sync_from_all, bool redirect_zone_set, std::string *redirect_zone,
                             bool is_master_set, bool *is_master, bool is_read_only_set,
                             bool *read_only, const list<std::string>& endpoints, list<std::string>& sync_from,
                             list<std::string>& sync_from_rm, CephContext *context, RGWRados *store,
                             Formatter *formatter);

int handle_opt_zonegroup_create(const std::string& zonegroup_id, const std::string& zonegroup_name, const std::string& realm_id,
                                const std::string& realm_name, const std::string& api_name, bool set_default, bool is_master,
                                const list<std::string>& endpoints, CephContext *context, RGWRados *store, Formatter *formatter);

int handle_opt_zonegroup_default(const std::string& zonegroup_id, const std::string& zonegroup_name, CephContext *context,
                                 RGWRados *store);

int handle_opt_zonegroup_delete(const std::string& zonegroup_id, const std::string& zonegroup_name, CephContext *context,
                                RGWRados *store);

int handle_opt_zonegroup_get(const std::string& zonegroup_id, const std::string& zonegroup_name, CephContext *context,
                             RGWRados *store, Formatter *formatter);

int handle_opt_zonegroup_list(CephContext *context, RGWRados *store, Formatter *formatter);

int handle_opt_zonegroup_modify(const std::string& zonegroup_id, const std::string& zonegroup_name, const std::string& realm_id,
                                const std::string& realm_name, const std::string& api_name, const std::string& master_zone,
                                bool is_master_set, bool is_master, bool set_default, const list<std::string>& endpoints,
                                CephContext *context, RGWRados *store, Formatter *formatter);

int handle_opt_zonegroup_set(const std::string& zonegroup_id, const std::string& zonegroup_name, const std::string& realm_id,
                             const std::string& realm_name, const std::string& infile,  bool set_default, const list<std::string>& endpoints,
                             CephContext *context, RGWRados *store, Formatter *formatter);

int handle_opt_zonegroup_remove(const std::string& zonegroup_id, const std::string& zonegroup_name, std::string& zone_id,
                                const std::string& zone_name, CephContext *context, RGWRados *store, Formatter *formatter);

int handle_opt_zonegroup_rename(const std::string& zonegroup_id, const std::string& zonegroup_name,
                                const std::string& zonegroup_new_name, CephContext *context, RGWRados *store);

int handle_opt_zonegroup_placement_list(const std::string& zonegroup_id, const std::string& zonegroup_name, CephContext *context,
                                        RGWRados *store, Formatter *formatter);

int handle_opt_zonegroup_placement_add(const std::string& placement_id, const std::string& zonegroup_id,
                                       const std::string& zonegroup_name, const list<std::string>& tags, CephContext *context,
                                       RGWRados *store, Formatter *formatter);

int handle_opt_zonegroup_placement_modify(const std::string& placement_id, const std::string& zonegroup_id,
                                          const std::string& zonegroup_name, const list<std::string>& tags,
                                          const list<std::string> tags_add, const list<std::string>& tags_rm,
                                          CephContext *context, RGWRados *store, Formatter *formatter);

int handle_opt_zonegroup_placement_rm(const std::string& placement_id, const std::string& zonegroup_id,
                                      const std::string& zonegroup_name, CephContext *context,
                                      RGWRados *store, Formatter *formatter);

int handle_opt_zonegroup_placement_default(const std::string& placement_id, const std::string& zonegroup_id,
                                           const std::string& zonegroup_name, CephContext *context, RGWRados *store,
                                           Formatter *formatter);

int handle_opt_zone_create(const std::string& zone_id, const std::string& zone_name, const std::string& zonegroup_id,
                           const std::string& zonegroup_name, std::string& realm_id, const std::string& realm_name,
                           const std::string& access_key, const std::string& secret_key, bool tier_type_specified,
                           std::string *tier_type, const map<std::string, std::string, ltstr_nocase>& tier_config_add,
                           bool sync_from_all_specified, bool *sync_from_all, bool redirect_zone_set,
                           std::string *redirect_zone, bool is_master_set, bool *is_master, bool is_read_only_set,
                           bool *read_only, const list<std::string>& endpoints, list<std::string>& sync_from,
                           list<std::string>& sync_from_rm, bool set_default, CephContext *context, RGWRados *store,
                           Formatter *formatter);

int handle_opt_zone_default(const std::string& zone_id, const std::string& zone_name, const std::string& zonegroup_id,
                            const std::string& zonegroup_name, CephContext *context, RGWRados *store);

int handle_opt_zone_delete(const std::string& zone_id, const std::string& zone_name, const std::string& zonegroup_id,
                           const std::string& zonegroup_name, CephContext *context, RGWRados *store);

int handle_opt_zone_get(const std::string& zone_id, const std::string& zone_name, CephContext *context, RGWRados *store,
                        Formatter *formatter);

int handle_opt_zone_set(std::string& zone_name, const std::string& realm_id, const std::string& realm_name, const std::string& infile,
                        bool set_default, CephContext *context, RGWRados *store, Formatter *formatter);

int handle_opt_zone_list(CephContext *context, RGWRados *store, Formatter *formatter);

int handle_opt_zone_modify(const std::string& zone_id, const std::string& zone_name, const std::string& zonegroup_id,
                           const std::string& zonegroup_name, std::string& realm_id, const std::string& realm_name,
                           const std::string& access_key, const std::string& secret_key, bool tier_type_specified,
                           std::string *tier_type, const map<std::string, std::string, ltstr_nocase>& tier_config_add,
                           const map<std::string, std::string, ltstr_nocase>& tier_config_rm,
                           bool sync_from_all_specified, bool *sync_from_all, bool redirect_zone_set,
                           std::string *redirect_zone, bool is_master_set, bool *is_master, bool is_read_only_set,
                           bool *read_only, const list<std::string>& endpoints, list<std::string>& sync_from,
                           list<std::string>& sync_from_rm, bool set_default, CephContext *context, RGWRados *store,
                           Formatter *formatter);

int handle_opt_zone_rename(const std::string& zone_id, const std::string& zone_name, const std::string& zone_new_name,
                           const std::string& zonegroup_id, const std::string& zonegroup_name,
                           CephContext *context, RGWRados *store);

int handle_opt_zone_placement_list(const std::string& zone_id, const std::string& zone_name, CephContext *context,
                                   RGWRados *store, Formatter *formatter);

int handle_opt_zone_placement_add(const std::string& placement_id, const std::string& zone_id, const std::string& zone_name,
                                  const boost::optional<std::string>& compression_type, const boost::optional<std::string>& index_pool,
                                  const boost::optional<std::string>& data_pool, const boost::optional<std::string>& data_extra_pool,
                                  bool index_type_specified, RGWBucketIndexType placement_index_type,
                                  CephContext *context, RGWRados *store, Formatter *formatter);

int handle_opt_zone_placement_modify(const std::string& placement_id, const std::string& zone_id, const std::string& zone_name,
                                     const boost::optional<std::string>& compression_type, const boost::optional<std::string>& index_pool,
                                     const boost::optional<std::string>& data_pool, const boost::optional<std::string>& data_extra_pool,
                                     bool index_type_specified, RGWBucketIndexType placement_index_type,
                                     CephContext *context, RGWRados *store, Formatter *formatter);

int handle_opt_zone_placement_rm(const std::string& placement_id, const std::string& zone_id, const std::string& zone_name,
                                 const boost::optional<std::string>& compression_type, CephContext *context, RGWRados *store,
                                 Formatter *formatter);

int handle_opt_metadata_sync_status(RGWRados *store, Formatter *formatter);

int handle_opt_metadata_sync_init(RGWRados *store);

int handle_opt_metadata_sync_run(RGWRados *store);

int handle_opt_data_sync_status(const std::string& source_zone, RGWRados *store, Formatter *formatter);

int handle_opt_data_sync_init(const std::string& source_zone, const boost::intrusive_ptr<CephContext>& cct, RGWRados *store);

int handle_opt_data_sync_run(const std::string& source_zone, const boost::intrusive_ptr<CephContext>& cct, RGWRados *store);

class RgwAdminMetadataSyncCommandsHandler : public RgwAdminCommandGroupHandler {
public:
  explicit RgwAdminMetadataSyncCommandsHandler(std::vector<const char*>& args, RGWRados* store,
                                               Formatter* formatter)
      : RgwAdminCommandGroupHandler(args, {"metadata", "sync"}, {
      {"status", OPT_METADATA_SYNC_STATUS},
      {"init",   OPT_METADATA_SYNC_INIT},
      {"run",    OPT_METADATA_SYNC_RUN},
  }, store, formatter) {
    if (parse_command_and_parameters(args) == 0) {
      std::cout << "Parsed command: " << m_command << std::endl;
    }
  }

  ~RgwAdminMetadataSyncCommandsHandler() override = default;

  // If parameter parsing failed, the value of m_command is OPT_NO_CMD and a call of this method
  // will return EINVAL
  int execute_command() override {
    switch (m_command) {
      case (OPT_METADATA_SYNC_STATUS) :
        return handle_opt_metadata_sync_status();
      case (OPT_METADATA_SYNC_INIT) :
        return handle_opt_metadata_sync_init();
      case (OPT_METADATA_SYNC_RUN) :
        return handle_opt_metadata_sync_run();
      default:
        return EINVAL;
    }
  }

  RgwAdminCommandGroup get_type() const override { return METADATA_SYNC; }

private:
  int parse_command_and_parameters(std::vector<const char*>& args) override;

  int handle_opt_metadata_sync_status() {
    return ::handle_opt_metadata_sync_status(m_store, m_formatter);
  }
  int handle_opt_metadata_sync_init() {
    return ::handle_opt_metadata_sync_init(m_store);
  }
  int handle_opt_metadata_sync_run() {
    return ::handle_opt_metadata_sync_run(m_store);
  }
};

class RgwAdminPeriodCommandsHandler : public RgwAdminCommandGroupHandler {
public:
  RgwAdminPeriodCommandsHandler(std::vector<const char*>& args, RGWRados* store, Formatter*
  formatter) : RgwAdminCommandGroupHandler(args, {"period"}, {{"commit",      OPT_PERIOD_COMMIT},
                                                              {"delete",      OPT_PERIOD_DELETE},
                                                              {"get",         OPT_PERIOD_GET},
                                                              {"get-current", OPT_PERIOD_GET_CURRENT},
                                                              {"list",        OPT_PERIOD_LIST},
                                                              {"pull",        OPT_PERIOD_PULL},
                                                              {"push",        OPT_PERIOD_PUSH},
                                                              {"update",      OPT_PERIOD_UPDATE}},
                                           store, formatter) {
    if (parse_command_and_parameters(args) == 0) {
      std::cout << "Parsed command:" << m_command << std::endl;
    }
  }

  ~RgwAdminPeriodCommandsHandler() override = default;

  int execute_command() override {
    switch (m_command) {
      case (OPT_PERIOD_COMMIT) :
        return handle_opt_period_commit();
      case (OPT_PERIOD_DELETE) :
        return handle_opt_period_delete();
      case (OPT_PERIOD_GET) :
        return handle_opt_period_get();
      case (OPT_PERIOD_GET_CURRENT) :
        return handle_opt_period_get_current();
      case (OPT_PERIOD_LIST) :
        return handle_opt_period_list();
      case (OPT_PERIOD_PULL) :
        return handle_opt_period_pull();
      case (OPT_PERIOD_PUSH) :
        return handle_opt_period_push();
      case (OPT_PERIOD_UPDATE) :
        return handle_opt_period_update();
      default:
        return EINVAL;
    }
  }

  RgwAdminCommandGroup get_type() const override { return PERIOD; }

private:
  int parse_command_and_parameters(std::vector<const char*>& args) override;

  int handle_opt_period_commit() {
    return ::handle_opt_period_commit(period_id, period_epoch, realm_id, realm_name, url,
                                      access_key, secret_key, remote, yes_i_really_mean_it,
                                      g_ceph_context, m_store, m_formatter);
  }

  int handle_opt_period_delete() {
    return ::handle_opt_period_delete(period_id, g_ceph_context, m_store);
  }

  int handle_opt_period_get() {
    return ::handle_opt_period_get(period_epoch, period_id, staging, realm_id, realm_name,
                                   g_ceph_context, m_store, m_formatter);
  }

  int handle_opt_period_get_current() {
    return ::handle_opt_period_get_current(realm_id, realm_name, m_store, m_formatter);
  }

  int handle_opt_period_list() {
    return ::handle_opt_period_list(m_store, m_formatter);
  }

  int handle_opt_period_pull() {
    return ::handle_opt_period_pull(period_id, period_epoch, realm_id, realm_name, url, access_key,
                                    secret_key, remote, g_ceph_context, m_store, m_formatter);
  }

  int handle_opt_period_push() {
    return ::handle_opt_period_push(period_id, period_epoch, realm_id, realm_name, url,
                                    access_key, secret_key, g_ceph_context, m_store);
  }

  int handle_opt_period_update() {
    return update_period(m_store, realm_id, realm_name, period_id, period_epoch,
                         commit, remote, url, access_key, secret_key, m_formatter,
                         yes_i_really_mean_it);
  }

  // TODO: add an option to generate access key
  std::string access_key;
  std::string secret_key;
  bool commit = false;
  std::string period_epoch;
  std::string period_id;
  std::string realm_id;
  std::string realm_name;
  std::string remote;
  bool staging = false;
  std::string url;
  bool yes_i_really_mean_it = false;
};

class RgwAdminRealmCommandsHandler : public RgwAdminCommandGroupHandler {
public:
  RgwAdminRealmCommandsHandler(std::vector<const char*>& args, RGWRados* store, Formatter*
  formatter) : RgwAdminCommandGroupHandler(args, {"realm"}, {{"create",       OPT_REALM_CREATE},
                                                             {"default",      OPT_REALM_DEFAULT},
                                                             {"delete",       OPT_REALM_DELETE},
                                                             {"get",          OPT_REALM_GET},
                                                             {"get-default",  OPT_REALM_GET_DEFAULT},
                                                             {"list",         OPT_REALM_LIST},
                                                             {"list-periods", OPT_REALM_LIST_PERIODS},
                                                             {"rename",       OPT_REALM_RENAME},
                                                             {"pull",         OPT_REALM_PULL},
                                                             {"set",          OPT_REALM_SET}},
                                           store, formatter) {
    if (parse_command_and_parameters(args) == 0) {
      std::cout << "Parsed command:" << m_command << std::endl;
    }
  }

  ~RgwAdminRealmCommandsHandler() = default;

  RgwAdminCommandGroup get_type() const override { return REALM; }

  int execute_command() override {
    switch (m_command) {
      case (OPT_REALM_CREATE) :
        return handle_opt_realm_create();
      case (OPT_REALM_DEFAULT) :
        return handle_opt_realm_default();
      case (OPT_REALM_DELETE) :
        return handle_opt_realm_delete();
      case (OPT_REALM_GET) :
        return handle_opt_realm_get();
      case (OPT_REALM_GET_DEFAULT) :
        return handle_opt_realm_get_default();
      case (OPT_REALM_LIST) :
        return handle_opt_realm_list();
      case (OPT_REALM_LIST_PERIODS) :
        return handle_opt_realm_list_periods();
      case (OPT_REALM_RENAME) :
        return handle_opt_realm_rename();
      case (OPT_REALM_PULL) :
        return handle_opt_realm_pull();
      case (OPT_REALM_SET) :
        return handle_opt_realm_set();
      default:
        return EINVAL;
    }
  }

private:
  int parse_command_and_parameters(std::vector<const char*>& args) override;

  int handle_opt_realm_create() {
    return ::handle_opt_realm_create(realm_name, set_default, g_ceph_context, m_store, m_formatter);
  }

  int handle_opt_realm_default() {
    return ::handle_opt_realm_default(realm_id, realm_name, g_ceph_context, m_store);
  }

  int handle_opt_realm_delete() {
    return ::handle_opt_realm_delete(realm_id, realm_name, g_ceph_context, m_store);
  }

  int handle_opt_realm_get() {
    return ::handle_opt_realm_get(realm_id, realm_name, g_ceph_context, m_store, m_formatter);
  }

  int handle_opt_realm_get_default() {
    return ::handle_opt_realm_get_default(g_ceph_context, m_store);
  }

  int handle_opt_realm_list() {
    return ::handle_opt_realm_list(g_ceph_context, m_store, m_formatter);
  }

  int handle_opt_realm_list_periods() {
    return ::handle_opt_realm_list_periods(realm_id, realm_name, m_store, m_formatter);
  }

  int handle_opt_realm_rename() {
    return ::handle_opt_realm_rename(realm_id, realm_name, realm_new_name, g_ceph_context, m_store);
  }

  int handle_opt_realm_pull() {
    return ::handle_opt_realm_pull(realm_id, realm_name, url, access_key, secret_key,
                                   set_default, g_ceph_context, m_store, m_formatter);
  }

  int handle_opt_realm_set() {
    return ::handle_opt_realm_set(realm_id, realm_name, infile, set_default, g_ceph_context,
                                  m_store, m_formatter);
  }

  // TODO: support generating access key
  std::string access_key;
  std::string secret_key;
  std::string infile;
  std::string realm_id;
  std::string realm_name;
  std::string realm_new_name;
  bool set_default = false;
  std::string url;
};

#endif //CEPH_RGW_ADMIN_MULTISITE_H
