////////////////////////////////////////////////////////////////////////////////////////////////////
// NoesisGUI - http://www.noesisengine.com
// Copyright (c) 2013 Noesis Technologies S.L. All Rights Reserved.
////////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

// RHI includes
#include "RHI.h"
#include "RHIResources.h"

// NoesisRuntime includes
#include "NoesisShaders.h"

// Noesis includes
#include "NoesisSDK.h"

// RenderCore includes
#include "ProfilingDebugging/RealtimeGPUProfiler.h"

class FNoesisRenderDevice : public Noesis::RenderDevice
{
	FVertexBufferRHIRef DynamicVertexBuffer;
	FIndexBufferRHIRef DynamicIndexBuffer;
	FUniformBufferRHIRef VSConstantBuffer;
	FUniformBufferRHIRef TextureSizeBuffer;
	FUniformBufferRHIRef PSConstantBuffer;
	FUniformBufferRHIRef EffectsBuffer;
	uint32 VSConstantsHash;
	uint32 TextureSizeHash;
	uint32 PSConstantsHash;
	uint32 EffectsHash;

#if WANTS_DRAW_MESH_EVENTS
	FDrawEvent* SetRenderTargetEvent;
	FDrawEvent* TileEvent;
#endif

	FNoesisRenderDevice();
	virtual ~FNoesisRenderDevice();

public:
	static uint32 RHICmdListTlsSlot;
	FVertexDeclarationRHIRef VertexDeclarations[Noesis::Shader::Count];
	TShaderRef<FNoesisVSBase> VertexShaders[Noesis::Shader::Count];
	TShaderRef<FNoesisPSBase> PixelShaders[Noesis::Shader::Count];
	TShaderRef<FNoesisPSBase> PixelShadersPatternSRGB[Noesis::Shader::Count];

	static FNoesisRenderDevice* Get();
	static void Destroy();

	static Noesis::Ptr<Noesis::Texture> CreateTexture(class UTexture* Texture);

	static void ThreadLocal_SetRHICmdList(class FRHICommandList* RHICmdList);
	static class FRHICommandList* ThreadLocal_GetRHICmdList();

	// RenderDevice interface
	virtual const Noesis::DeviceCaps& GetCaps() const override;
	virtual Noesis::Ptr<Noesis::RenderTarget> CreateRenderTarget(const char* Label, uint32 Width, uint32 Height, uint32 SampleCount) override;
	virtual Noesis::Ptr<Noesis::RenderTarget> CloneRenderTarget(const char* Label, Noesis::RenderTarget* SharedRenderTarget) override;
	virtual Noesis::Ptr<Noesis::Texture> CreateTexture(const char* Label, uint32 Width, uint32 Height, uint32 NumLevels, Noesis::TextureFormat::Enum TextureFormat, const void** Data) override;
	virtual void UpdateTexture(Noesis::Texture* Texture, uint32 Level, uint32 X, uint32 Y, uint32 Width, uint32 Height, const void* Data) override;
	virtual void BeginRender(bool Offscreen) override;
	virtual void SetRenderTarget(Noesis::RenderTarget* Surface) override;
	virtual void BeginTile(const Noesis::Tile& Tile, uint32 SurfaceWidth, uint32 SurfaceHeight) override;
	virtual void EndTile() override;
	virtual void ResolveRenderTarget(Noesis::RenderTarget* Surface, const Noesis::Tile* Tiles, uint32 NumTiles) override;
	virtual void EndRender() override;
	virtual void* MapVertices(uint32 Bytes) override;
	virtual void UnmapVertices() override;
	virtual void* MapIndices(uint32 Bytes) override;
	virtual void UnmapIndices() override;
	virtual void DrawBatch(const Noesis::Batch& Batch) override;
	// End of RenderDevice interface
};
