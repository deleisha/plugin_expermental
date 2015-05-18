#ifndef __OM_PROTO_H__
#define __OM_PROTO_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef struct schema_ver
{
    int32_t major;
    int32_t minor;
    int32_t fix;
} schema_ver;


struct main_svc;
typedef struct svc_hook
{
    const char *resource;
    const struct main_svc *platformServices;
} svc_hook;

/*
* Used by plugin manager to create and destroy the 
* plugins register this functions with PM
*/
typedef void * (*plgn_ctor)(svc_hook *);
typedef int32_t (*plgn_dtor)(void *);


//parameters being used by plugins for registrations.
//implementation langue of the plugin
typedef enum impl_lang
{
    C,
    //CPP,
    PYTHON
} Impl_lang;

//encapsulation of main application
typedef struct main_svc
{
    schema_ver vrsn;
    register_plgn registerObject;
    do_upcall invokeService;
} main_svc;


typedef struct plgn_info
{
    schema_ver vrsn;
    plgn_ctor createFunc;
    plgn_dtor destroyFunc;
    Impl_lang lang;
} plgn_info;


//implemented by PM for registering the plugins
typedef int32_t (*register_plgn)(const char *nodeType, const plgn_info *info);

//handle to main app , used for error reporting and logging
typedef int32_t (*do_upcall)(const char *svc_name, void *svc_params);


typedef int32_t (*plgn_exit)();
//being called by the entry point
typedef plgn_exit (*plgn_init)(const main_svc *);


plgn_exit entry_pt(const main_svc * svc);

#ifdef  __cplusplus
}
#endif
#endif /* __OM_PROTO_H__ */
