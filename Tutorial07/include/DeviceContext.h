#include "Prerequisities.h"
#pragma once

class DeviceContext
{
public:
DeviceContext() = default;
~DeviceContext() { SAFE_RELEASE(m_deviceContext) };

void
init();

void
update();

void
render();

void
destroy();

void
//Set an array of sampler states to the pixel shader pipeline stage.
PsSetSamplers(unsigned int StartSlot,
              unsigned int NumSamplers,
              ID3D11SamplerState* const* ppSamplers
);
void
//Number of indices to draw.
//The location of the first index read by the GPU from the index buffer.
DrawIndexed(unsigned int IndexCount,
            unsigned int StartIndexLocation,
            unsigned int BaseVertexLocation
);
void
//Bind an array of shader resources to the pixel shader stage.
PSSetShaderResources(UINT StartSlot,
                     UINT NumViews,
                     ID3D11ShaderResourceView* const* ppShaderResourceViews
);

void
//Sets the constant buffers used by the pixel shader pipeline stage
PSSetConstantBuffers(UINT StartSlot,
                     UINT NumBuffers,
                     ID3D11Buffer* const* ppConstantBuffers
);

void
//Sets a pixel shader to the device
PSSetShader(ID3D11PixelShader* pPixelShader,
            ID3D11ClassInstance* const* ppClassInstances,
            UINT NumClassInstances
);


void
//Sets the constant buffers used by the vertex shader pipeline stage. 
VSSetConstantBuffers(UINT StartSlot,
                     UINT NumBuffers,
                     ID3D11Buffer* const* ppConstantBuffers
);

void
//Set a vertex shader to the device.
VSSetShader(ID3D11VertexShader* pVertexShader,
            ID3D11ClassInstance* const* ppClassInstances,
            UINT NumClassInstances
);

void
//Pointer to the depth stencil to be cleared.
//Identify the type of data to clear
ClearDepthStencilView(ID3D11DepthStencilView* pDepthStencilView,
                      UINT ClearFlags,
                      FLOAT Depth,
                      UINT8 Stencil

);

void
//Set all the elements in a render target to one value.
ClearRenderTargetView(ID3D11RenderTargetView* pRenderTargetView,
                      const FLOAT ColorRGBA[4]
);

void
//Bind one or more render targets atomically and the depth-stencil buffer to the output-merger stage.
OMSetRenderTargets(UINT NumViews,
                   ID3D11RenderTargetView* const* ppRenderTargetViews,
                   ID3D11DepthStencilView* pDepthStencilView
);


void
//Bind an array of viewports to the rasterizer stage of the pipeline.
RSSetViewports(UINT NumViewports,
               const D3D11_VIEWPORT* pViewports
);

void
//Bind an input-layout object to the input-assembler stage.
IASetInputLayout(ID3D11InputLayout* pInputLayout
);

void
//Bind an array of vertex buffers to the input-assembler stage.
IASetVertexBuffers(UINT StartSlot,
                   UINT NumBuffers,
                   ID3D11Buffer* const* ppVertexBuffers,
                   const UINT* pStrides,
                   const UINT* pOffsets
);

void
//Bind an index buffer to the input-assembler stage.
IASetIndexBuffer(ID3D11Buffer* pIndexBuffer,
                 DXGI_FORMAT Format,
                 UINT Offset
);

void

IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY Topology
);




public:
//se igualan las variables que necesitamos
ID3D11DeviceContext* m_deviceContext = nullptr;
};
