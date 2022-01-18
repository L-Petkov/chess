#ifndef MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_RSRCMGR_H_
#define MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_RSRCMGR_H_


//C system includes

//C++ system includes

//Third-party includes

//Own includes
#include "manager_utils/managers/MgrBase.h"
#include "sdl_utils/containers/ImageContainer.h"
#include "sdl_utils/containers/TextContainer.h"
#include "sdl_utils/containers/FboContainer.h"

//Forward Declaration
struct RsrcMgrCfg;


class RsrcMgr: public MgrBase,
	public ImageContainer,
	public TextContainer,
	public FboContainer{

public:
	RsrcMgr() = default;
	RsrcMgr(const RsrcMgr& other) = delete;
	RsrcMgr(RsrcMgr&& other) = delete;

	RsrcMgr& operator=(const RsrcMgr& other) = delete;
	RsrcMgr& operator=(RsrcMgr&& other) = delete;

	int32_t init(const RsrcMgrCfg& cfg);
	void deinit() final;
	void process() final;



};
extern RsrcMgr* gRsrcMgr;


#endif /* MANAGER_UTILS_INCLUDE_MANAGER_UTILS_MANAGERS_RSRCMGR_H_ */
