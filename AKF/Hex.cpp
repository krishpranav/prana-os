
#include <AKF/Array.h>
#include <AKF/ByteBuffer.h>
#include <AKF/Hex.h>
#include <AKF/String.h>
#include <AKF/StringBuilder.h>
#include <AKF/StringView.h>
#include <AKF/Types.h>
#include <AKF/Vector.h>

namespace AKF {

Optional<ByteBuffer> decode_hex(const StringView& input)
{
    if ((input.length() % 2) != 0)
        return {};

    auto output = ByteBuffer::create_zeroed(input.length() / 2);

    for (size_t i = 0; i < input.length() / 2; ++i) {
        const auto c1 = decode_hex_digit(input[i * 2]);
        if (c1 >= 16)
            return {};

        const auto c2 = decode_hex_digit(input[i * 2 + 1]);
        if (c2 >= 16)
            return {};

        output[i] = (c1 << 4) + c2;
    }

    return output;
}

String encode_hex(const ReadonlyBytes input)
{
    StringBuilder output(input.size() * 2);

    for (auto ch : input)
        output.appendff("{:02x}", ch);

    return output.build();
}

}
