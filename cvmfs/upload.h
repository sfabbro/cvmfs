/**
 * This file is part of the CernVM File System.
 */

#ifndef CVMFS_UPLOAD_H_
#define CVMFS_UPLOAD_H_

#include <pthread.h>

#include <stdint.h>
#include <unistd.h>

#include <cstdio>
#include <string>

#include "atomic.h"


namespace upload {

class SpoolerBackend;
class Job;

// class BackendStat {
//  public:
//   BackendStat(const std::string &base_path) { base_path_ = base_path; }
//   virtual ~BackendStat() { }
//   virtual bool Stat(const std::string &path) = 0;
//  protected:
//   std::string base_path_;
// };


// class LocalStat : public BackendStat {
//  public:
//   LocalStat(const std::string &base_path) : BackendStat(base_path) { }
//   bool Stat(const std::string &path);
// };


// /**
//  * Encapsulates the callback function that handles responses from the external
//  * Spooler.
//  */
// class SpoolerCallbackBase {
//  public:
//   virtual void operator()(const std::string &path,
//                                   const int  retval,
//                           const std::string &digest) = 0;
// };

// class SpoolerCallback : public SpoolerCallbackBase {
//  public:
//   typedef void (*Callback)(const std::string &path,
//                            const int retval,
//                            const std::string &digest);

//   SpoolerCallback(Callback function) :
//     function_(function) {}

//   void operator()(const std::string &path,
//                           const int  retval,
//                   const std::string &digest) {
//     function_(path, retval, digest);
//   }

//  private:
//   Callback function_;
// };

// template <class DelegateT>
// class BoundSpoolerCallback : public SpoolerCallbackBase {
//  public:
//   typedef void (DelegateT::*Callback)(const std::string &path,
//                                       const int retval,
//                                       const std::string &digest);

//   BoundSpoolerCallback(DelegateT* delegate, Callback method) :
//     delegate_(delegate),
//     method_(method) {}
 
//   void operator()(const std::string &path,
//                           const int  retval,
//                   const std::string &digest) {
//     delegate_->*method_(path, retval, digest);
//   }

//  private:
//   DelegateT* delegate_;
//   Callback   method_;
// };


/**
 * Notifies the external spooler about files that are supposed to be uploaded to
 * the upstream storage.
 * Collects the results.  Files should only be sent once to the spooler,
 * otherwise there is no way to distinguish the results.
 * Internally, input and output work with two named pipes.
 * The callback function is called from a parallel thread.
 */
// class Spooler {
//  protected:

//   /**
//    * SpoolerDefinition is given by a string of the form:
//    * <spooler type>:<spooler description>
//    *
//    * F.e: local:/srv/cvmfs/dev.cern.ch
//    *      to define a local spooler with upstream path /srv/cvmfs/dev.cern.ch
//    */
//   struct SpoolerDefinition {
//     enum DriverType {
//       Riak,
//       Local,
//       Unknown
//     };

//     SpoolerDefinition(const std::string& definition_string);
//     bool IsValid() const { return valid_; }

//     DriverType  driver_type;
//     std::string spooler_description;
//     std::string upstream_urls;
//     std::string paths_out_pipe;
//     std::string digests_in_pipe;

//     bool valid_;
//   };

//  public:
//   /**
//    * Starts a spooler process and creates the corresponding object
//    * from a definition string which depends on the type of spooler to create.
//    *  - Local Spooler: "local:/dir/to/repo,/path/pipe,/digest/pipe"
//    *  -  Riak Spooler: "riak:http://riaknode1@...@http://riaknodeN,/path/pipe,/digest/pipe"
//    */
//   static Spooler *Construct(const std::string &definition_string);
//   virtual ~Spooler();

//   void SetCallback(SpoolerCallback *value) { spooler_callback_ = value; }
//   void UnsetCallback() { delete spooler_callback_; spooler_callback_ = NULL; }
//   SpoolerCallback *spooler_callback() { return spooler_callback_; }

//   void SpoolProcess(const std::string &local_path,
//                     const std::string &remote_dir,
//                     const std::string &file_suffix);
//   void SpoolCopy(const std::string &local_path, const std::string &remote_path);
//   void EndOfTransaction();

//   void set_move_mode(const bool mode) { move_mode_ = mode; }

//   bool IsIdle() { return atomic_read64(&num_pending_) == 0; }
//   void WaitFor();
//   uint64_t num_errors() { return atomic_read64(&num_errors_); }

//  protected:
//   Spooler(const SpoolerDefinition &spooler_definition);
//   bool Connect(const std::string &fifo_paths,
//                const std::string &fifo_digests);

//  private:
//   static void *MainReceive(void *caller);

//   template <class PushWorkerT>
//   void SpawnSpoolerBackend(const SpoolerDefinition &definition);

//   SpoolerBackend *backend_;
//   bool move_mode_;
// };

// BackendStat *GetBackendStat(const std::string &spooler_definition);

}  // namespace upload

#include "upload_impl.h"

#endif  // CVMFS_UPLOAD_H_
