/*
 * Copyright (C) 2020 Linux Studio Plugins Project <https://lsp-plug.in/>
 *           (C) 2020 Vladimir Sadovnikov <sadko4u@gmail.com>
 *
 * This file is part of lsp-plugins
 * Created on: 21 нояб. 2018 г.
 *
 * lsp-plugins is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * lsp-plugins is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with lsp-plugins. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef DSP_ARCH_NATIVE_GRAPHICS_EFFECTS_H_
#define DSP_ARCH_NATIVE_GRAPHICS_EFFECTS_H_

#ifndef __DSP_NATIVE_IMPL
    #error "This header should not be included directly"
#endif /* __DSP_NATIVE_IMPL */

namespace native
{
    void eff_hsla_hue(float *dst, const float *v, const dsp::hsla_hue_eff_t *eff, size_t count)
    {
        float value, hue, alpha;
        float t     = 1.0f - eff->thresh;
        float kt    = 1.0f / eff->thresh;

        for (size_t i=0; i<count; ++i, dst += 4)
        {
            value   = v[i];
            value   = (value >= 0.0f) ? 1.0f - value : 1.0f + value;

            if (value < t)
            {
                hue         = eff->h + value;
                alpha       = 0.0f;
            }
            else
            {
                hue         = eff->h + t;
                alpha       = ((value - t) * kt);
            }

            dst[0]      = (hue > 1.0f) ? hue - 1.0f : hue;
            dst[1]      = eff->s;
            dst[2]      = eff->l;
            dst[3]      = alpha;
        }
    }

    void eff_hsla_alpha(float *dst, const float *v, const dsp::hsla_alpha_eff_t *eff, size_t count)
    {
        float value;

        for (size_t i=0; i<count; ++i, dst += 4)
        {
            value   = v[i];
            value   = (value >= 0.0f) ? 1.0f - value : 1.0f + value;

            dst[0]  = eff->h;
            dst[1]  = eff->s;
            dst[2]  = eff->l;
            dst[3]  = value; // Fill alpha channel
        }
    }

    void eff_hsla_sat(float *dst, const float *v, const dsp::hsla_sat_eff_t *eff, size_t count)
    {
        float value;
        float kt = 1.0f / eff->thresh;

        for (size_t i=0; i<count; ++i, dst += 4)
        {
            value   = v[i];
            value   = (value >= 0.0f) ? value : -value;

            if (value >= eff->thresh)
            {
                dst[0]      = eff->h;
                dst[1]      = eff->s * value;
                dst[2]      = eff->l;
                dst[3]      = 0.0f;
            }
            else
            {
                dst[0]      = eff->h;
                dst[1]      = eff->s * eff->thresh;
                dst[2]      = eff->l;
                dst[3]      = (eff->thresh - value) * kt;
            }
        }
    }

    void eff_hsla_light(float *dst, const float *v, const dsp::hsla_light_eff_t *eff, size_t count)
    {
        float value;
        float kt = 1.0f / eff->thresh;

        for (size_t i=0; i<count; ++i, dst += 4)
        {
            value   = v[i];
            value   = (value >= 0.0f) ? value : -value;

            if (value >= eff->thresh)
            {
                dst[0]      = eff->h;
                dst[1]      = eff->s;
                dst[2]      = eff->l * value;
                dst[3]      = 0.0f;
            }
            else
            {
                dst[0]      = eff->h;
                dst[1]      = eff->s;
                dst[2]      = eff->l * eff->thresh;
                dst[3]      = (eff->thresh - value) * kt;
            }
        }
    }
}

#endif /* DSP_ARCH_NATIVE_GRAPHICS_EFFECTS_H_ */
